#Cry of Fear Server Browser

#CHANGELOG
#V1.0.0.0
- Initial Release

#V1.0.0.1
- You now connect to servers when double clicking items in the server list, before it would only copy the ip and port and you had to paste it in the console when the game was up.
- Now you can also connect to other servers while CoF is running by double clicking any available server, this will tell the running game to connect to it.
- You can now right click any item in the server list, this will pop up a context menu where you can choose to connect to the server or show info about the active players on the server. You can quick refresh this Player Info form by hitting F5.

#V1.0.0.2
- Fixed a crash which would occur if you closed the program while searching for servers.
- Fixed an issue when you'd connect to a server when CoF wasn't running it had a 50-50 chance that you would not be connected to the server. (you had to click the server again when CoF was up)
- You can now see which servers are password protected. (displays a padlock icon)
- The server browser has a separate executable for Win XP users, move the CoFServerBrowser.exe from the 'winXP' folder and into the same folder as the .NET 4.5 CoFServerBrowser and overwrite it.

#ABOUT
This program was written in C++ by Bernt Andreas Eide, I was sick of standing idle for so long after the standalone release/steampipe updates which broke the integrated server browser for CoF.
Now you're finally able to see active servers for CoF.
Unfortunately it isn't possible to host dedicated servers at this time because the programmer for CoF did some ineffective donation checks on the server side which ends up in the server crashing when there's no client in it (host). I've tried to use fakeclients/bots using third party plugins but this didn't solve the issue. One can only wish for the devs to fix this at some point, if it is possible.
The source code for this program is available at my GitHub profile 'BerntA' if you want to modify it or use it for something else.

Other Notable Credits:
Arvuti - CoF Art(startup screen img)
Team Psykskallar - CoF Devs
Joshikumako - Testing

#INSTRUCTIONS
You can use the F5 shortcut to update/refresh the server list.
The Play button in the context menu allows you to open the game right away, this has been added to bypass the launcher and allowing you to start CoF with unique launch options like changing your port number for online play.

Because I bypass the launcher I have no idea which resolution you want to have which is why I generate a file in the .exe's directory named 'settings.txt', this file contains the default startup params (custom) for CoF.
By default the resolution will be set to your primary desktop resolution and it will be set to fullscreen.
To change this open up the settings.txt file and change the -w & -h manually.
You can also add your own startup cmds here!

To join a server you have to double click an item in the server list.
You can also join servers in this app while CoF is running, it will redirect the connection to the game and you will auto-connect to the new server!

You can also right click any item in the server list, this will pop up a context menu which allows you to click on 'Connect to Server' or 'Show Players'
If you click on 'Show Players' you'll be able to see all the active players on the server you selected, to quick refresh the list click F5, to quick close click ESC!

Have fun!

#INSTALL INSTRUCTIONS
Extract the contents of the .rar file wherever you like except for the Cry of Fear directory. 
If you extract the files into the Cry of Fear directory (common/Cry of Fear) you will break the game because this application runs a newer version of SteamAPI. (overrides CoF's steam_api.dll)
However you can put it into "common/Cry of Fear/cryoffear/" if you really want to.
When everything is extracted launch the .exe and have fun!

##FOR WINDOWS XP USERS:
Because .NET 4.5 doesn't work for WIN XP I have made a .NET 4.0 version inside the 'winXP' folder, move it over to the base folder and overwrite the .NET 4.5 executable!

If the program doesn't open/crashes make sure you have the latest .NET Framework and the latest C/C++ redist.
###Links:
- https://support.microsoft.com/en-us/kb/2977003
- https://www.microsoft.com/en-us/download/details.aspx?id=42642

#HOW DO I HOST A SERVER / HOW TO MAKE MY SERVER VISIBLE ON THE INTERNET
First write 192.168.1.1 in your web browser which will normally be the IP to your router, it may promt a username and password.
Once you're logged in you have to find something called Port Forwarding.
Once you find that, add a new rule and forward the port 27015 via UDP (default for source and gold source). You also have to specify the internal IP on your local network.
To find your internal IP open up the command promt (WIN-KEY + R then write cmd and hit enter), type ipconfig then hit enter. 
Write down your IPv4 address and port forward on that ip.

Now restart your router if necessary, open CoF, make sure sv_lan is 0 and that's it!
A handy command to write in the console @ CoF is heartbeat (sort of like refresh).

If you want to port forward another port you'll have to add +port <portNumber> to the settings.txt file so it networks through that port instead of the default 27015 one.

#CONTACT / HELP
If you require any further assistance feel free to add me on steam : TFOBernt @ STEAM_0:0:7019991
