set(SOURCE_FILES 
        src/DiscordRichPresence/DiscordManager.h
        src/DiscordRichPresence/DiscordManager.cpp
        src/DiscordRichPresence/discord_game_sdk/discord.h
        )
add_library(DiscordRichPresence STATIC ${SOURCE_FILES})
target_link_libraries(DiscordRichPresence PUBLIC ClientNet ClientLib discord_game_sdk)
target_include_directories(DiscordRichPresence PUBLIC src/)