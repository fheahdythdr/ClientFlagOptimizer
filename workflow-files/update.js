const simpleGit = require('simple-git');

const names = ["DFFlag"];
const values = [500];
const includes = ["FFlag"];

const repo = simpleGit();
await repo.clone('https://github.com/username/repo.git', 'localdir');

(async () => {
    const fs = require('fs')
    const fetch = await import('node-fetch').then(m => m.default)
    const data = await fetch("https://raw.githubusercontent.com/L8X/Roblox-Client-Optimizer/main/ClientAppSettings.json")
    const Settings = await data.json()
    const New = {};
    for (const name of Object.keys(Settings)) {
        if (includes.some((val) => name.includes(val)) || names.some((val) => name.startsWith(val)) || values.some((val) => Settings[name] == val)) {
            New[name] = Settings[name];
        }
    }
    fs.writeFileSync('localdir/ClientAppSettings.json', JSON.stringify(New));
})()

await repo.cwd('localdir').add(filePath).commit('Update file').push();
