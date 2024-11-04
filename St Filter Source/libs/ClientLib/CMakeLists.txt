
set(SOURCE_FILES src/BufRender.h
    src/CameraWorking.cpp
    src/CameraWorking.h
    src/Client.cpp
    src/Client.h
    src/Data/ActionWndData.h
    src/Data/CharacterData.h
    src/Data/DropGoldData.h
        src/Data/GachaNpcData.h
    src/Data/GameGuideData.h
    src/Data/ItemData.h
    src/Data/LevelData.h
    src/Data/LevelGoldData.h
    src/Data/MagicOptionData.h
    src/Data/MallItemMenuListData.h
    src/Data/MessageTipData.h
    src/Data/NPCChatData.h
    src/Data/NPCPosData.h
    src/Data/QuestData.h
    src/Data/RefPackageItemData.h
    src/Data/RefPricePolicyOfItem.h
    src/Data/RefScrapOfPackageItemData.h
    src/Data/RefShopdata.h
    src/Data/RefShopTabData.h
    src/Data/RefShopTabGroupData.h
    src/Data/ShopItemStockPeriod.h
    src/Data/ShopItemStockQuantity.h
    src/Data/TeleportBuilding.h
    src/Data/TeleportData.h
    src/Data/TeleportLink.h
    src/DxSound.h
    src/EntityManagerClient.h
    src/Game.cpp
    src/Game.h
    src/GEffSound.h
    src/GEffSoundBody.cpp
    src/GEffSoundBody.h
    src/GInterface.cpp
    src/GInterface.h
        src/GlobalDataManager.cpp
        src/GlobalDataManager.h
    src/GlobalHelpersThatHaveNoHomeYet.h
    src/GObj.h
    src/IDxSound.h
    src/IFAction.h
    src/IFApprenticeShip.h
    src/IFApprenticeShipSlot.h
    src/IFButton.cpp
    src/IFButton.h
    src/IFChatViewer.cpp src/IFChatViewer.h
    src/IFCloseButton.cpp
    src/IFCloseButton.h
    src/IFConsole.h
    src/IFDecoratedStatic.cpp
    src/IFDecoratedStatic.h
    src/IFDragableArea.cpp
    src/IFDragableArea.h
    src/IFEdit.h
    src/IFEquipment.h
    src/IFFade.h
    src/IFFrame.cpp
    src/IFFrame.h
    src/IFGauge.h
    src/IFHelperBubbleWindow.h
    src/IFInventory.h
    src/IFMainFrame.cpp
    src/IFMainFrame.h
        src/IFMainPopup.h
    src/IFNPCTalk.h
    src/IFNPCWindow.h
    src/IFParty.h
    src/IFPartySlot.h
    src/IFPlayerInfo.h
    src/IFPlayerMiniInfo.cpp
    src/IFPlayerMiniInfo.h
    src/IFPractice.h
    src/IFQuest.h
    src/IFQuickStateHalfWnd.h
    src/IFQuickStateWnd.h
    src/IFScrollManager.h
    src/IFSelectableArea.h
        src/IFSkill.h
    src/IFSkillBoard.h
    src/IFSkillPracticeBox.h
    src/IFSlotWithHelp.h
    src/IFSpinButtonCtrl.h
    src/IFStatic.cpp
    src/IFStatic.h
    src/IFStaticWithPictureClip.h
    src/IFSystemMessage.cpp
    src/IFSystemMessage.h
    src/IFStorageRoom.h
    src/IFStoreForPackage.h
    src/IFStretchWnd.h
    src/IFSupporterChatWnd.h
    src/IFTextBox.h
    src/IFTileWnd.cpp
    src/IFTileWnd.h
    src/IFTimerWnd.h
    src/IFWnd.cpp
    src/IFWnd.h
    src/IObject.h src/IObject.cpp
    src/IRMManager.cpp
    src/IRMManager.h
    src/is_this_important.cpp
    src/is_this_important.h
    src/MessageBoxManager.h
    src/NavigationDeadreckon.cpp
    src/NavigationDeadreckon.h
    src/PSilkroad.cpp
    src/PSilkroad.h
    src/PSOuterInterface.cpp
    src/PSOuterInterface.h
    src/PSVersionCheck.cpp
    src/PSVersionCheck.h
    src/RTLoading.cpp
    src/RTLoading.h
    src/StdAfx.cpp
    src/StdAfx.h
    src/StringUtils.h
    src/TextBoard.cpp
    src/TextBoard.h
    src/unsorted.cpp
    src/unsorted.h
    src/AlramGuideMgrWnd.cpp src/AlramGuideMgrWnd.h
    src/IFConfirmReputationGuide.cpp src/IFConfirmReputationGuide.h
    src/IFEventGuide.cpp src/IFEventGuide.h
    src/IFQuestInfoGuide.cpp src/IFQuestInfoGuide.h
    src/IFLetterAlarmGuide.cpp src/IFLetterAlarmGuide.h
    src/IFServerEventGuide.cpp src/IFServerEventGuide.h
    src/IFOpenMarketAlramGuide.cpp src/IFOpenMarketAlramGuide.h
    src/IFEventGuideSecond.cpp src/IFEventGuideSecond.h
    src/IFflorian0Guide.cpp src/IFflorian0Guide.h
    src/PSQuickStart.cpp
    src/PSQuickStart.h
    src/NIFUnderMenuBar.cpp src/NIFUnderMenuBar.h
    src/TextStringManager.cpp src/TextStringManager.h
    src/IFNotify.cpp src/IFNotify.h
    src/IFListCtrl.cpp src/IFListCtrl.h
    src/LinkedScroll.cpp src/LinkedScroll.h
    src/IFVerticalScroll.cpp src/IFVerticalScroll.h
    src/IFScrollBar.cpp src/IFScrollBar.h
    src/IFTextBox.cpp src/IFTextBox.h
    src/IFSelectableArea.cpp src/IFSelectableArea.h
    src/IFChatModeViewer.cpp src/IFChatModeViewer.h
    src/ICPlayer.h src/ICPlayer.cpp
    src/SOItem.h
    src/ICUser.cpp src/ICUser.h
    src/IFEdit.cpp src/IFEdit.h
    src/SRO_MSG_DEF.h
    src/CharacterDependentData.cpp src/CharacterDependentData.h
    src/NIFCommunityWnd.cpp src/NIFCommunityWnd.h
    src/NIFBlockWnd.cpp src/NIFBlockWnd.h
    src/ICharactor.cpp src/ICharactor.h
    src/ClassLink.h
    src/IGIDObject.cpp src/IGIDObject.h
    src/IFNotify.cpp src/IFNotify.h
        src/NetProcessIn.h
    src/NetProcessSecond.cpp src/NetProcessSecond.h
    src/NetProcessThird.cpp src/NetProcessThird.h
    src/PSMission.cpp src/PSMission.h
    src/GameCfg.cpp src/GameCfg.h
    src/LocalTime.cpp src/LocalTime.h src/IFflorian0.cpp src/IFflorian0.h src/CPSMission.cpp src/CPSMission.h src/IFEquipment.cpp src/IFHelperBubbleWindow.cpp src/IFInventory.cpp src/IFMainPopup.cpp src/IFSlotWithHelp.cpp src/ObjectData.h src/SOItem.cpp src/IFTaiXiuIcon.cpp src/IFTaiXiuIcon.h src/hook.cpp src/hook.h src/MemoryHack.cpp src/MemoryHack.h src/CPSTitle.cpp src/CPSTitle.h src/xlib.h src/IFNapThe.cpp src/IFNapThe.h src/NetProcessIn.cpp src/GlobalDataManager.cpp src/IFSkill.cpp src/NotificationHandler.cpp src/NotificationHandler.h src/CMsgStreamBuffer.cpp src/CMsgStreamBuffer.h src/IFStretchWnd.cpp src/IFCheckBox.cpp src/IFCheckBox.h src/IFChatOptionBoard.cpp src/IFChatOptionBoard.h src/IFNormalTile.cpp src/IFNormalTile.h src/IFDANGKYEVENT.cpp src/IFDANGKYEVENT.h src/IFConsole.cpp src/IFDailyLoginIcon.h src/IFSlotWithHelpForPackage.cpp src/IFSlotWithHelpForPackage.h src/ICCos.cpp src/ICCos.h src/IFTest.cpp src/IFTest.h src/IFWholeChat.cpp src/IFWholeChat.h src/CInterfaceNetSender.cpp src/CInterfaceNetSender.h src/IFSpinButtonCtrl.cpp src/IFflorian0Runtime.cpp src/IFflorian0Runtime.h src/IFDailyLoginIcon.cpp src/IFSTChest.cpp src/IFSTChest.h src/IFSTChestSlotList.cpp src/IFSTChestSlotList.h src/IFSTChestSlot.cpp src/IFSTChestSlot.h src/IFSpinControl.cpp src/IFSpinControl.h src/IFSTOldLogin.cpp src/IFSTOldLogin.h src/Packet.cpp src/Packet.h src/memhelp.cpp src/memhelp.h src/IFSTChangeGrantName.cpp src/IFSTChangeGrantName.h src/IFSTDpsMetter.cpp src/IFSTDpsMetter.h src/IFSTCharLock.cpp src/IFSTCharLock.h src/IFSTUniqueHistory.cpp src/IFSTUniqueHistory.h src/IFSTUniqueHistorySlotList.cpp src/IFSTUniqueHistorySlotList.h src/IFSTUniqueHistorySlot.cpp src/IFSTUniqueHistorySlot.h src/Rebot.cpp src/Rebot.h src/Skill.h src/ChatViewerItemAction.cpp src/ChatViewerItemAction.h src/GameDataExt.cpp src/GameDataExt.h src/IFSTSwitchTitle.cpp src/IFSTSwitchTitle.h src/IFSTCustomTitle.cpp src/IFSTCustomTitle.h src/IFSTConfirm.cpp src/IFSTConfirm.h src/IFSTCustomRank.cpp src/IFSTCustomRank.h src/IFSTCustomRankList.cpp src/IFSTCustomRankList.h src/IFSTCustomRankSlot.cpp src/IFSTCustomRankSlot.h src/IFSTTaiXiu.cpp src/IFSTTaiXiu.h src/ICharactor_Class1.cpp src/ICharactor_Class1.h src/ICharactor_Class2.cpp src/ICharactor_Class2.h src/ICharactor_Class3.cpp src/ICharactor_Class3.h src/ICharactor_Class4.cpp src/ICharactor_Class4.h src/IFSTChestIcon.cpp src/IFSTChestIcon.h src/IFSTEventTime.cpp src/IFSTEventTime.h src/IFSTEventTimeSlot.cpp src/IFSTEventTimeSlot.h src/IFSTEventTimeSlotList.cpp src/IFSTEventTimeSlotList.h src/IFSTSurvivalKills.cpp src/IFSTSurvivalKills.h src/IFSTDailyLogin.cpp src/IFSTDailyLogin.h src/IFSTTotalPoints.cpp src/IFSTTotalPoints.h src/IFSTTotalPointSlot.cpp src/IFSTTotalPointSlot.h src/IFSTTotalPointSlotList.cpp src/IFSTTotalPointSlotList.h src/IFSTEventRegister.cpp src/IFSTEventRegister.h src/IFSTEventRegisterSlot.cpp src/IFSTEventRegisterSlot.h src/IFSTEventRegisterSlotList.cpp src/IFSTEventRegisterSlotList.h src/IFSTEventXoSoMienBac.cpp src/IFSTEventXoSoMienBac.h src/IFSTEventXoSoMienBacLichSu.cpp src/IFSTEventXoSoMienBacLichSu.h src/IFSTEventXoSoMienBacLichSuSlot.cpp src/IFSTEventXoSoMienBacLichSuSlot.h src/IFSTEventXoSoMienBacLichSuSlotList.cpp src/IFSTEventXoSoMienBacLichSuSlotList.h src/IFSTLotteryEvent.cpp src/IFSTLotteryEvent.h src/IFSTPvpChallenge.cpp src/IFSTPvpChallenge.h src/IFSTPvpChallengeAnswer.cpp src/IFSTPvpChallengeAnswer.h src/NIFWorldMap.cpp src/NIFWorldMap.h src/AnimationCallback.cpp src/AnimationCallback.h src/CObjAnimation.cpp src/CObjAnimation.h src/CompSimple.cpp src/CompSimple.h src/PSCharacterSelect.cpp src/PSCharacterSelect.h src/World.cpp src/World.h src/IFFade.cpp src/Keyframe.cpp src/Keyframe.h src/IFChatWndCtrl.cpp src/IFChatWndCtrl.h src/IFMessageBoxButton.cpp src/IFMessageBoxButton.h src/IFMessageBox.cpp src/IFMessageBox.h src/MemoryHelper.cpp src/MemoryHelper.h src/IFSTCharacterIcons.cpp src/IFSTCharacterIcons.h src/UserGuildInfo.cpp src/UserGuildInfo.h src/PartyData.h src/PartyMemberData.h src/IFSTReverseScrollPlus.cpp src/IFSTReverseScrollPlus.h src/IFSTReverseScrollPlusSlotList.cpp src/IFSTReverseScrollPlusSlotList.h src/IFSTReverseScrollPlusSlot.cpp src/IFSTReverseScrollPlusSlot.h src/IFSTFTWCounter.cpp src/IFSTFTWCounter.h src/Data/CharacterData.cpp src/IFSTCustomNPC.cpp src/IFSTCustomNPC.h src/IFSTCustomNPCList.cpp src/IFSTCustomNPCList.h src/IFSTCustomNPCSlot.cpp src/IFSTCustomNPCSlot.h src/IFSTCharItemInfo.cpp src/IFSTCharItemInfo.h src/Pathfinder.cpp src/Pathfinder.h src/Node.cpp src/Node.h src/node_set.h src/IFSTExtraFeature.cpp src/IFSTExtraFeature.h src/OptimizeCloth.cpp src/OptimizeCloth.h src/ICharInfo.h src/ChatItemLink.h src/IFReBotIcon.cpp src/IFReBotIcon.h src/IItem.h src/IFSTPetFilter.cpp src/IFSTPetFilter.h src/IFCOS.cpp src/IFCOS.h src/IFPlayerInfo.cpp src/IFCOSSetup.cpp src/IFCOSSetup.h src/IFSliderCtrl.cpp src/IFSliderCtrl.h src/CharacterStatistics.h "src/HWID Manager/utility.cpp" "src/HWID Manager/utility.h" "src/HWID Manager/memmgr.cpp" "src/HWID Manager/memmgr.h" "src/HWID Manager/md5.cpp" "src/HWID Manager/md5.h" "src/HWID Manager/hwidmgr.cpp" "src/HWID Manager/hwidmgr.h" "src/HWID Manager/CPacket.cpp" "src/HWID Manager/CPacket.h" "src/HWID Manager/CEncryption.cpp" "src/HWID Manager/CEncryption.h" "src/HWID Manager/common.h" "src/HWID Manager/LoadHWID.cpp" "src/HWID Manager/LoadHWID.h" src/HWID/base64.cpp src/HWID/base64.h src/HWID/Base64Encode.h src/HWID/HawidManager.cpp src/HWID/HawidManager.h src/HWID/md5.cpp src/HWID/md5.h src/IFPartyMatchReqJoin.cpp src/IFPartyMatchReqJoin.h src/IFPartyMatch.cpp src/IFPartyMatch.h src/IFPartySlot.cpp src/IFParty.cpp src/IFSTStreamSetting.cpp src/IFSTStreamSetting.h src/IFSTStremSettingIcon.cpp src/IFSTStremSettingIcon.h src/IFTargetWindowJobPlayer.cpp src/IFTargetWindowJobPlayer.h src/IFBuffViewer.cpp src/IFBuffViewer.h src/IFTargetWindowPlayer.cpp src/IFTargetWindowPlayer.h src/IFTargetWindowCommonEnemy.cpp src/IFTargetWindowCommonEnemy.h src/IFTargetWindowFortressStructure.cpp src/IFTargetWindowFortressStructure.h src/IFTargetWindowSpecialMob.cpp src/IFTargetWindowSpecialMob.h src/IFTargetWindow.cpp src/IFTargetWindow.h src/ICNonuser.cpp
        src/ICNonuser.h src/ICNonuser.cpp
        src/ICMonster.cpp src/ICMonster.h src/IFSTConfimUrl.cpp src/IFSTConfimUrl.h src/NIFGuildWnd.cpp src/NIFGuildWnd.h src/NIFButton.cpp src/NIFButton.h src/IFMagicStateBoard.cpp src/IFMagicStateBoard.h src/IFSTMacro.cpp src/IFSTMacro.h src/IFSTMacroAutoHunt.cpp src/IFSTMacroAutoHunt.h src/IFPartyMatchSlot.cpp src/IFPartyMatchSlot.h src/IFSTPartyMatchMemberViewer.cpp src/IFSTPartyMatchMemberViewer.h src/IFSTPartyMatchMemberViewerSlot.cpp src/IFSTPartyMatchMemberViewerSlot.h src/IFSTPartyMatchMemberViewerSlotList.cpp src/IFSTPartyMatchMemberViewerSlotList.h src/IFExtQuickSlot.cpp src/IFExtQuickSlot.h src/IFExtQuickSlotSlot.cpp src/IFExtQuickSlotSlot.h src/IFSlotWithHelpEx.cpp src/IFSlotWithHelpEx.h src/NIFWnd.cpp src/IFExtQuickSlotSecond.cpp src/IFExtQuickSlotSecond.h src/IFExtQuickSlotOption.cpp src/IFExtQuickSlotOption.h src/IFExtQuickSecondSlotOption.cpp src/IFExtQuickSecondSlotOption.h src/IFCircularMenuSlot.cpp src/IFCircularMenuSlot.h src/IFCircularMenuFrame.cpp src/IFCircularMenuFrame.h src/IFCircularMenu.cpp src/IFCircularMenu.h src/IFSTEffect.cpp src/IFSTEffect.h src/NIFStatic.cpp src/NIFFrame.cpp src/NIFFrame.h src/NIFTileWnd.cpp src/NIFTileWnd.h src/NIFDragableArea.cpp src/NIFDragableArea.h src/NIFMainFrame.cpp src/NIFMainFrame.h src/NIFTextBoard.cpp src/NIFTextBoard.h src/IGIDObjectCustom.h src/NIRMManager.cpp src/NIRMManager.h src/IFCOSInfo.cpp src/IFCOSInfo.h src/IFCOSInventory.cpp src/IFCOSInventory.h src/IFPetMiniInfo.cpp src/IFPetMiniInfo.h src/IFSTMacroAutoBuffSlot.cpp src/IFSTMacroAutoBuffSlot.h src/IFSTMacroAutoBuffSlotList.cpp src/IFSTMacroAutoBuffSlotList.h src/IFSTMacroAutoBuffSkillSlot.cpp src/IFSTMacroAutoBuffSkillSlot.h src/IFSTMacroAutoBuffSkillSlotList.cpp src/IFSTMacroAutoBuffSkillSlotList.h src/IFSTMacroAutoBuffedSkillSlot.cpp src/IFSTMacroAutoBuffedSkillSlot.h src/IFSTMacroAutoBuffedSkillSlotList.cpp src/IFSTMacroAutoBuffedSkillSlotList.h src/SilkRoadWeb/SilkroadWeb.cpp src/SilkRoadWeb/SilkroadWeb.h src/Data/GachaItemSetData.h src/IFSTBloodEffect.cpp src/IFSTBloodEffect.h src/IFSTBattleRoyaleKillCount.cpp src/IFSTBattleRoyaleKillCount.h src/Data/IItem.cpp src/Data/IItem.h src/DropItemManager.cpp src/DropItemManager.h)



add_library(ClientLib STATIC ${SOURCE_FILES})
target_link_libraries(ClientLib GFXMainFrame GFX3DFunction GFXFileManagerLIB NavMesh ClientNet SimpleViewer TypeId abi-testing imgui remodel ghidra)
target_include_directories(ClientLib PUBLIC src/)
