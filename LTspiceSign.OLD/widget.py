# This Python file uses the following encoding: utf-8
import argparse
import logging, logging.handlers
import hashlib
import json
import os, os.path
import time
import warnings
import sys

#from requests.packages.urllib3.fields import RequestField
from urllib3.fields import RequestField
# from requests.packages.urllib3.filepost import encode_multipart_formdata
from urllib3.filepost import  encode_multipart_formdata
from urllib.parse import urljoin
import requests
import yaml
import glob
import re
import shutil

warnings.filterwarnings('ignore', message='Unverified HTTPS request')

__version__ = "0.1.3"

from PySide6.QtWidgets import QApplication, QWidget
from PySide6.QtCore import QTimer



# Important:
# You need to run the following command to generate the ui_form.py file
#     pyside6-uic form.ui -o ui_form.py, or
#     pyside2-uic form.ui -o ui_form.py
from ui_form import Ui_Widget


def argparse_setup():
    parser = argparse.ArgumentParser(
        prog="gen_signature_kmi",
        description="Generature signatures, to be used for development until global ops solution is available.",
        epilog="",
    )

    parser.add_argument(
        "-u", "--user",
        help="The user name.",
        action='store',
        required=False
    )

    parser.add_argument(
        "-p", "--password",
        help="The user password.",
        action='store',
        required=False
    )

    parser.add_argument(
        "-c", "--configuration",
        help="Configuration yml file",
        action='store',
        required=False
    )

    parser.add_argument(
        "-s", "--server",
        help="Server URL",
        action='store',
        required=False
    )

    parser.add_argument(
        "-k", "--key-profile",
        help="CSG signing profile",
        action='store',
        required=False
    )

    parser.add_argument(
        "-g", "--group-name",
        help="CSG group name",
        action='store',
        required=False
    )

    parser.add_argument(
        "-i", "--input-file",
        help="Binary input file (secure boot header).",
        action='store',
        required=False
    )

    parser.add_argument(
        "-o", "--output-file",
        help="Signature in binary format..",
        action='store',
        required=False
    )

    parser.add_argument(
        "-r", "--request_only",
        help="Only send a signing request and do not wait for the signature. Download the signature separately.",
        action='store_true',
        required=False
    )

    parser.add_argument(
        "-d", "--download_only",
        help="Download previous approved request -d [requestID]",
        action='store_true',
        required=False
    )

    parser.add_argument(
        "-v", "--version",
        action='version',
        version=f"\n%(prog)s version {__version__}.\n"
    )

    return parser


def logging_setup(no_debug=False):
    logger = logging.getLogger(__name__)
    logger.setLevel(logging.DEBUG)

    LOG_FILENAME = "kmi-signature.log"

    # Log to file
    fh = logging.handlers.RotatingFileHandler(LOG_FILENAME, maxBytes=2 ** 20, backupCount=1)
    formatter = logging.Formatter('%(asctime)s - %(levelname)-10s | %(message)s', "%Y-%m-%d %H:%M:%S")
    fh.setFormatter(formatter)
    # Only for the log file, adjust the log level for messages saved
    if no_debug:
        fh.setLevel(logging.INFO)
    else:
        fh.setLevel(logging.DEBUG)
    logger.addHandler(fh)

    # Also log to STDOUT
    ch = logging.StreamHandler(sys.stdout)
    formatter = logging.Formatter('%(levelname)-10s | %(message)s')
    ch.setFormatter(formatter)
    ch.setLevel(logging.INFO)
    logger.addHandler(ch)

    return logger


def downloadSignature(output_file, hostname, creds, reqId):
    urlreq = urljoin(hostname, f"/api/csgAPI/downloadFile?requestid={reqId}")

    res = requests.get(urlreq, auth=creds, verify=False)

    try:
        with open(output_file, 'wb') as f:
            f.write(res.content)
    except:
        log.error(f"Error opening signature file '{output_file}'")
        return 1

    if (os.stat(output_file).st_size == 0):
        log.error("Empty Signature!")
        return 1
    else:
        log.info(f"signature written to '{output_file}'")

    return 0


def uploadFileForSignature(hostname, creds, profileId, groupId, args):
    filepath = args.input_file
    fname = os.path.basename(filepath)

    with open(filepath, "rb") as ifile:
        inputfile = ifile.read()

    filehash = hashlib.sha256(inputfile).hexdigest()
    log.debug(f"'{filepath}' sha-256 digest is: {filehash}")

    metadata = {'SigningProfileId': profileId, 'groupId': groupId, 'fileHashSha256': filehash.upper()}
    jsdata = json.dumps(metadata)

    files = {'data': (None, jsdata, 'text/plain'),
             'file': (fname, inputfile, 'text/plain')}

    fields = []
    for name, (filename, contents, mimetype) in files.items():
        rf = RequestField(name=name, data=contents,
                          filename=filename)
        rf.make_multipart(content_disposition='attachment', content_type=mimetype)
        fields.append(rf)

    post_body, content_type = encode_multipart_formdata(fields)
    content_type = ''.join(('multipart/mixed',) + content_type.partition(';')[1:])

    headers = {'Content-Type': content_type}

    requrl = urljoin(hostname, "api/csgAPI/createRequest")

    r = requests.post(requrl, auth=creds, data=post_body, headers=headers, verify=False)

    statuscode = r.status_code

    if ((statuscode == 200) and (r.json()['returnCode']['errorCode'] == 0)):
        log.info("Signing request submitted")
    else:
        errorCode = r.json()['returnCode']['errorCode']
        errorString = r.json()['returnCode']['errorString']
        log.error(f"Signing Request Error: {errorCode} - {errorString}")
        sys.exit(1)

    try:
        reqId = r.json()['request']['requestId']
        log.info(f"Request is {reqId}")
    except KeyError as e:
        log.error("Request failed")
        sys.exit(1)

    return (statuscode, reqId)


def waitFileSig(hostname, creds, reqId):
    log.info(f"Waiting for request {reqId} to finish")

    getStatusURL = urljoin(hostname, f"api/csgAPI/getRequestStatus?requestID={reqId}")

    status = None

    maxtries = 100
    sleepsec = 1

    log.info(f"will query server with {sleepsec} second delay, up to {maxtries} times")

    for attempt in range(1, maxtries + 1):
        statusreq = requests.get(getStatusURL, auth=creds, verify=False)
        status = statusreq.json()[0]['request']['requestStatus']
        if status == "CompletedSuccess":
            log.info(f"signature complete on query #{attempt}")
            break
        if (status == "CompletedFailed"
                or status == "Denied"
                or status == "Cancelled"):
            log.error(f"signature came back on query #{attempt} as '{status}'")
            sys.exit(1)
        time.sleep(sleepsec)
    else:
        log.error(f"timed out after {maxtries} queries for signature completion")
        sys.exit(1)


def listSigningProfiles(hostname, creds):
    url = "https://" + hostname + "/api/csgAPI/listSigningProfiles"
    r = requests.get(url, auth=creds, verify=False)
    return r


# https://swharden.com/blog/2021-05-15-python-credentials/
def getCredentials(defaultUser):
    import tkinter
    root = tkinter.Tk()
    root.eval('tk::PlaceWindow . center')
    root.title('Login KMI Signature Request')
    uv = tkinter.StringVar(root, value=defaultUser)
    pv = tkinter.StringVar(root, value='')
    userEntry = tkinter.Entry(root, bd=3, width=50, textvariable=uv)
    passEntry = tkinter.Entry(root, bd=3, width=50, show="*", textvariable=pv)
    btnClose = tkinter.Button(root, text="OK", command=root.destroy)
    userEntry.pack(padx=10, pady=5)
    passEntry.pack(padx=10, pady=5)
    btnClose.pack(padx=10, pady=5, side=tkinter.TOP, anchor=tkinter.NE)
    root.mainloop()
    return [uv.get(), pv.get()]


def processPendingRequests(creds, output_file):
    tempfilelist = []
    for file in glob.glob(output_file + "[0-9]*.json.tmp"):
        match = re.search(r'\d+', file)
        if match:
            reqid = int(match.group())
            tempfilelist.append((reqid, file))

    # get highest request id in list and try to complete download
    tempfilesbyreqid = sorted(tempfilelist, key=lambda x: x[0], reverse=True)

    reqfile = tempfilesbyreqid[0][1]

    with open(reqfile, "r") as jsonfile:
        reqfiledata = jsonfile.read()

    req = json.loads(reqfiledata)

    status = downloadSignature(os.path.join(os.path.dirname(output_file), req["outputfile"]), req["hostname"], creds,
                               req["reqId"])

    if (status == 0):
        os.remove(reqfile)


class Widget(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.timer = None
        self.current_position = None
        self.log_file_path = None
        self.ui = Ui_Widget()
        self.ui.setupUi(self)
        self.ui.SignButton.clicked.connect(self.signDocuments)

    def signDocuments(self):
        # if args.configuration is not None:
        parser = argparse_setup()
        log = logging_setup()
        args = parser.parse_args()

        cfg = {}
        args.configuration = "LTspice.yml"

        if args.configuration is not None:
            try:
                with open(args.configuration, "r") as cf:
                    cfg = yaml.safe_load(cf)
            except FileNotFoundError:
                raise
            except yaml.YAMLError:
                raise Exception(f"Error reading configuration file: {args.configuration}")

        # get back None if option was not present in yaml file (excluded or misspelled field)
        kmuser = cfg.get('username', None)
        password = cfg.get('password', None)
        hosts = cfg.get('serverList', None)
        profileName = cfg.get('signingProfileName', None)
        groupName = cfg.get('signingGroupName', None)

        # If these are passed by command line they can override the config file
        if args.user is not None:
            kmuser = args.user

        if args.password is not None:
            password = args.password

        if args.key_profile is not None:
            profileName = args.key_profile

        if args.group_name is not None:
            groupName = args.group_name

        if password is None:
            kmuser, password = getCredentials("kmiusername")

        creds = (kmuser, password)
        log.info(f"using credentials of '{kmuser}'")

        hostname = None

        if args.server is not None:
            hosts = [args.server]
            log.info(f"attempting to use '{args.server}'")
        else:
            log.info("searching available servers")

        # complain if missing required things
        if kmuser is None:
            raise Exception("missing 'kmuser'.")
        if password is None:
            raise Exception("missing 'password'.")
        if hosts is None:
            raise Exception(
                "missing 'hosts' list or single server. Please specify on commandline or in configuration file.")
        if profileName is None:
            raise Exception("missing 'profileName'. Please specify on commandline or in configuration file.")
        if groupName is None:
            raise Exception("missing 'groupName'. Please specify on commandline or in configuration file.")

        if args.download_only:
            processPendingRequests(creds, args.output_file)

        else:
            for url in hosts:
                log.debug(f"trying '{url}'")
                try:
                    resp = listSigningProfiles(url, creds)
                except requests.exceptions.ConnectionError as e:
                    log.warning(f"Failed to connect to server '{url}'")
                    log.debug(e)
                    log.warning("double-check server name")
                    continue

                if (resp.status_code == 200):
                    hostname = url
                    profiles = resp.json()['signingProfiles']
                    break
                log.warning(f"Failed to connect to server '{url}'")
                log.debug(f"{resp.status_code} - {resp.reason}")
                if (resp.status_code == 401):
                    log.warning("double-check credentials")

            if hostname is None:
                log.error("No suitable kmi server found")
                sys.exit(1)
            log.info(f"using kmi server '{hostname}'")

            log.info(f"using signing profile '{profileName}' in group '{groupName}'")
            profiles = [p for p in profiles if p['signingProfileName'] == profileName
                        if p['groupName'] == groupName]
            if len(profiles) < 1:
                log.error("Requested profile/group combination not available")
                log.warning("double-check profile/group names and credential permissions")
                sys.exit(1)
            else:
                profId = profiles[0]['signingProfileId']
                groupId = profiles[0]['groupId']

            hostname = 'https://' + hostname

            log.info(f"Sending signing request to '{hostname}'")

            if self.ui.LTspiceRadioButton.isChecked():
                args.input_file = "/Users/German.Ergueta/LTspiceDevelopment/VersionsWindows" +  "/" + self.ui.LTspiceVersion.text() + "/unsigned/" + self.ui.LTspiceFilename.text()
                args.output_file = "/Users/German.Ergueta/LTspiceDevelopment/VersionsWindows" +  "/" + self.ui.LTspiceVersion.text() + "/signed/" + self.ui.LTspiceFilename.text()
            if self.ui.LTspiceMsiRadioButton.isChecked():
                args.input_file = "/Users/German.Ergueta/LTspiceDevelopment/VersionsWindows" +  "/" + self.ui.LTspiceVersion.text() + "/unsigned/" + self.ui.LTspiceMsiFilename.text()
                args.output_file = "/Users/German.Ergueta/LTspiceDevelopment/VersionsWindows" +  "/" + self.ui.LTspiceVersion.text() + "/signed/" + self.ui.LTspiceMsiFilename.text()

            # upload the input file for signature
            status, reqId = uploadFileForSignature(hostname, creds, profId, groupId, args)

            if not args.request_only:
                waitFileSig(hostname, creds, reqId)

                # get the signature
                status = downloadSignature(args.output_file, hostname, creds, reqId)

                sys.exit(status)
            else:
                with open(args.output_file + str(reqId) + ".json.tmp", "w") as req_idtmpfile:
                    req = dict()
                    req["reqId"] = reqId
                    req["hostname"] = hostname
                    req["inputfile"] = args.input_file
                    req["outputfile"] = os.path.basename(args.output_file)

                    req_idtmpfile.write(json.dumps(req))

            # Initialize log file reading
            self.log_file_path = "path/to/your/logfile.log"
            current_position = 0  # To track the current reading position in the file

            # Set up a QTimer to update the text edit periodically
            self.timer = QTimer(self)
            self.timer.timeout.connect(self.update_log)
            self.timer.start(1000)  # Update every second (1000 milliseconds)

    def update_log(self):
        try:
            # Open the file in read mode and start reading from the current position
            with open(self.log_file_path, 'r') as file:
                file.seek(self.current_position)  # Go to the last read position
                new_data = file.read()  # Read new data
                self.current_position = file.tell()  # Update current position

                if new_data:
                    self.information.append(new_data)  # Append new data to the QTextEdit
        except Exception as e:
            self.text_edit.append(f"Error: Unable to read log file.\n{e}")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    parser = argparse_setup()
    log = logging_setup()
    args = parser.parse_args()

    widget = Widget()
    widget.show()


    sys.exit(app.exec())
