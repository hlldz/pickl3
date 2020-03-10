# Pickl3
Pickl3 is Windows active user credential phishing tool. You can execute the Pickl3 and phish the target user credential.
![](https://raw.githubusercontent.com/hlldz/pickl3/master/pickl3.png)

## Operational Usage - 1
Nowadays, since the operating system of many end users is Windows 10, we cannot easily steal account information with Mimikatz-like projects like the old days. Using Pickl3, you can try to steal the account information of the active user without escalating the privileges.

## Operational Usage - 2

Nowadays, there are approximately 200 announced sandbox detection methods. Sandboxes, especially analyzing in the Hypervisor layer, are immune to these detection methods. But sandboxes aren't so good at user interaction yet. You can get an advantage by using Pickl3 in your developed malware. For example, end users are generally targeted in today's Red Team operations. The end users targeted have a password, and as long as the user you are targeting does not enter their password correctly, you can prevent your malware from working and bypass the possible sandbox control. However, it would be good if you prevent your malware from working with Administrator rights during the first installation. Because, in sandboxes, malwares are generally analyzed in Administrator rights.
