(async () => {
    const simpleGit = require('simple-git');
    const user = process.env.gituser;
    const pass = process.env.gitpass

    const names = ["DFFlag"];
    const values = [500];
    const includes = ["FFlag"];

    const repo = simpleGit();
    repo.env({ ...process.env, GIT_SSH_COMMAND: 'ssh -o StrictHostKeyChecking=no' });
    await repo.clone(`https://${user}:${pass}@github.com/fheahdythdr/rco-but-it-uses-different-fflags`, '');
    const fs = require('fs')
    const data = await fetch("https://raw.githubusercontent.com/L8X/Roblox-Client-Optimizer/main/ClientAppSettings.json")
    const Settings = await data.json()
    const New = {};
    for (const name of Object.keys(Settings)) {
        if (includes.some((val) => name.includes(val)) || names.some((val) => name.startsWith(val)) || values.some((val) => Settings[name] == val)) {
            New[name] = Settings[name];
        }
    }
    if (fs.readFileSync('/ClientAppSettings.json', 'utf8') != JSON.stringify(New)) {
        fs.writeFileSync('/ClientAppSettings.json', JSON.stringify(New));
    }
})()
