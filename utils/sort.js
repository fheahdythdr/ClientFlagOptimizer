// add in your own custom values here.
/*
  * here's how they work:
    * names: if the name of the key contains this, it gets added
    * values: if the value of the key is the value, it gets added
  * so, if you want to add FInts:
    * you add "FInt" into names.
  * you want to have some specific value:
    * you add value to values, ex. 0.
*/

const names = ["FFlag"];
const values = [500];


(async () => {
    const fs = require('fs')
    fs.writeFileSync(__dirname + '/write.lua', ``)
    const fetch = await import('node-fetch').then(m => m.default)
    const data = await fetch("https://raw.githubusercontent.com/L8X/Roblox-Client-Optimizer/main/ClientAppSettings.json")
    const Settings = await data.json()
    const New = {};
    for (const name of Object.keys(Settings)) {
        if (names.some((val) => name.includes(val)) || values.some((val) => Settings[name] == val)) {
            New[name] = Settings[name];
        }
    }
    fs.writeFileSync(__dirname + '/test.json', JSON.stringify(New));
})()
