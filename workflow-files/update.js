(async () => {
    /*const names = ["DFFlag"];
    const values = [500];
    const includes = ["FFlag"];
    const fs = require('fs')*/
    const data = await fetch("https://cdn.discordapp.com/attachments/1101725468815798322/1115958516851675146/ClientAppSettings.json");
    //const fdata = await fetch("https://raw.githubusercontent.com/L8X/Roblox-Client-Optimizer/main/assets/flagversion.rco");
    //const fflagver = await fdata.text();
    const Settings = await data.json()
    /*const New = {};
    for (const name of Object.keys(Settings)) {
        if (includes.some((val) => name.includes(val)) || names.some((val) => name.startsWith(val)) || values.some((val) => Settings[name] == val)) {
            if (name.includes("TaskSchedulerTargetFps")) Settings[name] = 999999
            New[name] = Settings[name];
        }
    }*/
    fs.writeFileSync('./rco-but-it-uses-different-fflags/ClientAppSettings.json', JSON.stringify(Settings, null, 2));
    //fs.writeFileSync('./rco-but-it-uses-different-fflags/flagversion.rco', fflagver);
})()
