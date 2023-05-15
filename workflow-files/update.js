(async () => {
    const names = ["DFFlag"];
    const values = [500];
    const includes = ["FFlag"];
    const fs = require('fs')
    const data = await fetch("https://roblox-client-optimizer.simulhost.com/ClientAppSettings.json")
    const Settings = await data.json()
    const New = {};
    for (const name of Object.keys(Settings)) {
        if (includes.some((val) => name.includes(val)) || names.some((val) => name.startsWith(val)) || values.some((val) => Settings[name] == val)) {
            New[name] = Settings[name];
        }
    }
    fs.writeFileSync('./rco-but-it-uses-different-fflags/ClientAppSettings.json', JSON.stringify(New));
})()
