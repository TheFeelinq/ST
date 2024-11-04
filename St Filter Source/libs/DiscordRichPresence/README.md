# sro-discord-rpc
Attract more players by using Discord Rich Presence on Silkroad Online!

### Features
- Game status
- Charname, level, and guildname if exists
- Elapsed time after login
- Job mode status
- Region name and his related image (is not shown if is in job mode)
- Updates level, and regions almost in realtime!
- It won't affect client performance

### Preview
<img title="User Preview" src="https://i.imgur.com/Ii2G3JQ.png">

### Starter Guide:
1. Create an application on [discord developer portal](https://www.elitepvpers.com/link/?https://discord.com/developers/applications)
2. Fill some data there but take note about your app **CLIENT ID**
3. Then go to _Rich Presence > Art Assets_ and upload all the images from folder `source/libs/DiscordRichPresence/assets`
4. Open your Visual Studio 20XX and set your **CLIENT ID** into `source/DevKit_DLL/src/Util.cpp`
5. Download [Discord Game SDK](https://dl-game-sdk.discordapp.net/2.5.6/discord_game_sdk.zip)
6. Extract from SDK the file `lib/x86/discord_game_sdk.dll` to your silkroad folder
7. Build/compile or/and inject it as normally you do it with SRO_DevKit and it's done!

> Source: https://github.com/JellyBitz/sro-discord-rpc/