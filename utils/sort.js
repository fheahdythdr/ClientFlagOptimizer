/*
  * here's how the names and values arrays work:
    * names: if the name of the key starts with this, it gets added
    * values: if the value of the key is the value, it gets added
    * includes: if the name of the key includes this, it gets added
  * so, if you want to add FInts:
    * you add "FInt" into names.
  * if you want to specifically add DFFlags:
    * you add "DFFlag" into names.
  * you want to have some specific value:
    * you add value to values, ex. 0.
  * if you want to find other fflags and add them in, go to https://github.com/MaximumADHD/Roblox-Client-Tracker/blob/roblox/FVariables.txt
  * keep in mind you'll have to search through them manually and apply values to them manually
  * here's how they work
    * FFlags are boolean values, set them to true or false
    * FInts are number values, set them to a number
    * FStrings are strings, set them to a string (ex. "opt-out")
  * this takes from the current json in l8x's repo
*/

const names = ["DFFlag"];
const values = [500];
const includes = ["FFlag"];


(async () => {
    const fs = require('fs')
    fs.writeFileSync(__dirname + '/write.lua', ``)
    const fetch = await import('node-fetch').then(m => m.default)
    const data = await fetch("https://raw.githubusercontent.com/L8X/Roblox-Client-Optimizer/main/ClientAppSettings.json")
    const Settings = await data.json()
    const New = {};
    for (const name of Object.keys(Settings)) {
        if (includes.some((val) => name.includes(val)) || names.some((val) => name.startsWith(val)) || values.some((val) => Settings[name] == val)) {
            New[name] = Settings[name];
        }
    }
    fs.writeFileSync(__dirname + '/test.json', JSON.stringify(New));
})()
