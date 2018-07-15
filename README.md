## Screenshot:  
![Alt text](Screenshot1.png?raw=true "")
![Alt text](Screenshot2.png?raw=true "")

## Building:  
Compile using project file sqlite-browser.pro file (from QtCreator IDE or cmd).  

## Files:  
main.cpp - main file :)  
MainWindow.[h|cpp|ui] - Main window with ui file. Most of the stuff happens here ;)  
*.png - Some standard Qt icons did not fit. I've added 2 simple one to fill the gap.  
icons.qrc - Qt resources file with icons location.  
DatabaseConfig.[h|cpp]- File with all needed info for creation of DB structure + user friendly names.  
AddRowDialog.[h|cpp|ui] - Dialog window used whew user want to add new record in DB.  

## Additional info  
Potential further improvements:  
1) Make fully generic creation of DB and use of things related to database structure.  
2) Use json file as DB structure definition (would fill DatabaseConfig class).  

I'm not fully happy about:  
1) Point 1 above.  
2) Got some problems with focus. There still might be scenarios when current item is set on table view but row is not selected (delete row action active because of that).  
