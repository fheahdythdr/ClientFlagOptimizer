## About

Roblox Client Optimizer tweaks flags to optimize your Roblox client. Click [here](https://github.com/fheahdythdr/rco-but-it-uses-different-fflags/releases) to download our latest version.

As of now, it seems like the main RCO repo is going towards using NodeJS to run the installer and the main file.

This repo is staying in C++, and I will try my best to implement any features they add into this version.

If any errors happen, create an issue and try to explain what happened or provide a video of what happened.

## Features

When using the source repo's URL (https://roblox-client-optimizer.simulhost.com/ClientAppSettings.json), you'll get these.
- Unlocks FPS (frames per second)
- Optimizes caching, graphics, and textures
- Increases user privacy
- Disables Crashpad & Backtrace crash metrics
- Disables large portions of client telemetry
- Disables `AbuseReportScreenshot`
- Enables font preloading and texture item preloading
- Enables `Memory Prioritization` and `Performance Control`
- Gives you more graphics quality options (21 instead of 10)
- Enables `Quick Game Launch`
- Enables the `Parallel Humanoid Manager`
- Enables `Batch Asset Api`
- Allows you to switch JSON urls
When using a custom URL, it'll depend what gets activated in the url.

## Question & Answer

- Why not manually install flags?
  - Manually installing flags is time consuming. When Roblox updates, you must remember to install the flag file manually again, while Roblox Client Optimizer will handle this operation automatically.
  - If a major bug is found within the flag file, there is no way for us to notify you to update it, therefore we've implemented measures to automatically update our flag list if such a problem arose.
- Will the software slow down my computer?
  - **No**, the software is very lightweight and only checks for updates to our flag list and updates to itself. Additionally, we use a content delivery network powered by [Cloudflare](https://www.cloudflare.com) and [Fastly](https://www.fastly.com) to optimize the bandwidth usage and file size of any flag file or downloads that the software makes.
- Will I get banned for using this?
  - **No**, our operations are fully compliant with the [Roblox Terms of Use](https://help.roblox.com/hc/articles/115004647846-Roblox-Terms-of-Use), and we use a method that [Roblox](https://www.roblox.com) themselves intentionally added to the client to modify flags. Roblox Client Optimizer remains operational regardless of anti-cheat measures, as we do not inject a DLL nor modify live client memory - our software is not an exploit, or a tool used to aid in exploiting.
- What are flags?
  - The Roblox engine uses a system called fast flags as part of the deployment process. When code is shipped, not all of it is active by default. Rather, the changes are enabled and disabled dynamically via `FFlags`, even after the code is live in production. We welcome you to read more about flags [here](https://devforum.roblox.com/t/254517) and [here](https://github.com/MaximumADHD/Roblox-FFlag-Tracker).

## Disclaimers

- Do we collect and store user data?
  - **No**, the program itself does not collect **ANY** data, telemetry, or analytics from our users. The only possible data transferred is due to your use of Roblox Client Optimizer, where the IP address of your devices is required to connect to the internet and therefore update Roblox Client Optimizer and the flag list, however our content delivery providers have an agreement with us called a Data Processing Addendum, which restricts them from using your data (just your IP address) outside of delivering the files to you that Roblox Client Optimizer requests.
- What happens to time wasting issues and pull requests?
  - Posting time wasting issues and pull requests may result in your account being blocked from the repository. Please ensure all contributions are meaningful and correct. Before posting an issue, try to make sure there is not already one regarding your issue, if there is, we welcome you to comment on it.

## Using custom URLS

To use a custom ClientAppSettings.json url, make a file called custom_url.txt in C:\RCO2.
Put the custom url in that file, and relaunch RCO2.
It has to be the raw URL that gives the raw JSON, like raw github urls.
If you want some configs, go to [my fflag repo](https://github.com/fheahdythdr/rco-fflags)

### GDPR, CCPA & Coppa Disclosure

We are **NOT** a data handler or processor, for any queries relating to data transmitted via the network traffic of Roblox Client Optimizer (keep in mind your IP address is disclosed to every website you visit), please contact [Cloudfare](https://www.cloudfare.com), [Fastly](https://www.fastly.com), and [Microsoft](https://www.microsoft.com) directly.
