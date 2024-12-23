USE [SRO_VT_SHARDLOG]
GO
/****** Object:  StoredProcedure [dbo].[_AddLogChar]    Script Date: 13/8/2022 1:03:57 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


ALTER   procedure [dbo].[_AddLogChar] 
@CharID        int,
@EventID        tinyint,
@Data1        int,
@Data2        int,
@strPos        varchar(64),
@Desc        varchar(128)
as
	declare @len_pos 	int
	declare @len_desc	int
	set @len_pos = len(@strPos)
	set @len_desc = len(@Desc)
	if (@len_pos > 0 and @len_desc > 0)
	begin	
		insert _LogEventChar values(@CharID, GetDate(), @EventID, @Data1, @Data2, @strPos, @Desc)	
	end
	else if (@len_pos > 0 and @len_desc = 0)
	begin 	
		insert _LogEventChar (CharID, EventTime, EventID, Data1, Data2, EventPos) values(@CharID, GetDate(), @EventID, @Data1, @Data2, @strPos)
	end
	else if (@len_pos = 0 and @len_desc > 0)
	begin 	
		insert _LogEventChar (CharID, EventTime, EventID, Data1, Data2, strDesc) values(@CharID, GetDate(), @EventID, @Data1, @Data2, @Desc)
	end
	else
	begin
		insert _LogEventChar (CharID, EventTime, EventID, Data1, Data2) values(@CharID, GetDate(), @EventID, @Data1, @Data2)
	end
--- ip logs
/* coded by alexiuns */
IF (@EventID = 4 Or @EventID = 6)
BEGIN
BEGIN TRANSACTION
BEGIN TRY


COMMIT TRANSACTION
END TRY
BEGIN CATCH
SELECT
ERROR_NUMBER() AS ErrorNumber,
ERROR_SEVERITY() AS ErrorSeverity,
ERROR_STATE() AS ErrorState,
ERROR_PROCEDURE() AS ErrorProcedure,
ERROR_LINE() AS ErrorLine,
ERROR_MESSAGE() AS ErrorMessage

ROLLBACK TRANSACTION
END CATCH
IF (@@ERROR <> 0)
BEGIN
RETURN
ROLLBACK TRANSACTION
END
END


-- Main Declares
  DECLARE @GM_Prim int =(select sec_primary from SRO_VT_ACCOUNT.dbo.TB_User as us inner join SRO_VT_SHARD.dbo._User as us2
        on us.JID = us2.UserJID where CharID = @CharID)
DECLARE @CharName varchar(50) = (SELECT CharName16 FROM SRO_VT_SHARD.dbo._Char WHERE CharID = @CharID ) 

--------------


	 IF (@EventID = 4 or @EventID = 6 or @EventID = 9 OR @EventID = 11)  
    BEGIN  
	declare @JobTypes int = (select JobType from SRO_VT_SHARD.._CharTrijob where CharID=@CharID)
	declare @JobLevel int = (select Level from SRO_VT_SHARD.._CharTrijob where CharID=@CharID)
	update SRO_VT_PROXY.._TotalPointRanking set JobLevel = @JobLevel Where CharName = @CharName
	update SRO_VT_PROXY.._TotalPointRanking set JobType = @JobTypes Where CharName = @CharName
    EXEC SRO_VT_PROXY.[dbo].[_SumPoint] @CharName
	 --EXEC SRO_VT_PROXY.[dbo].[_BattleRoyaleBackupAndClearINV] @CharID
	 --EXEC SRO_VT_PROXY.[dbo].[_RestoreCharINV] @CharID
	--EXEC SRO_VT_PROXY.[dbo]._GiveLevelBuff @CharName
    END  	  
--- add to filter
	IF (@EventID = 4)
	BEGIN 
			declare @Date2 date = GETDATE()-1
		IF NOT EXISTS(SELECT CharName FROM SRO_VT_PROXY.[dbo]._DaiLyLogin WITH(NOLOCK) WHERE CharName = @CharName)
			begin
			INSERT INTO SRO_VT_PROXY.[dbo]._DaiLyLogin (CharName,DiemDanh,Nhan1Ngay,Nhan3Ngay,Nhan5Ngay,Nhan7Ngay,Nhan10Ngay,Nhan13Ngay,Nhan16Ngay,Nhan19Ngay,Nhan22Ngay,Nhan25Ngay,LastLogin) VALUES (@CharName,1,0,0,0,0,0,0,0,0,0,0,getdate())
			END
		IF EXISTS(SELECT CharName FROM SRO_VT_PROXY.._DaiLyLogin WITH (NOLOCK) WHERE CharName = @CharName AND LastLogin = @Date2)
			BEGIN
			UPDATE SRO_VT_PROXY.[dbo]._DaiLyLogin   SET LastLogin = getdate()-1  WHERE CharName = @CharName
			END
		IF NOT EXISTS(SELECT CharName FROM SRO_VT_PROXY.[dbo]._TotalPointRanking WITH(NOLOCK) WHERE CharName = @CharName)
			begin
			INSERT INTO SRO_VT_PROXY.[dbo]._TotalPointRanking (CharName,HonorPoint,JobKill,UniqueKill,BattleArenaWin,CapFlagWin,FTWKill,JobbingPoint,SurvivalKill,ItemPoints,DailyJobPoints,JobType,JobLevel) VALUES (@CharName,0,0,0,0,0,0,0,0,0,0,@JobTypes,@JobLevel)
			END

				
		--	IF NOT EXISTS(SELECT CharName FROM SRO_VT_PROXY.[dbo]._LogTichNap WITH(NOLOCK) WHERE CharName = @CharName)
			--begin
			--INSERT INTO SRO_VT_PROXY.[dbo]._LogTichNap (CharName,DaNap,DaNhan1,DaNhan2,DaNhan3,DaNhan4,DaNhan5,DaNhan6,DaNhan7,DaNhan8,DaNhan9,DaNhan10) VALUES (@CharName,0,0,0,0,0,0,0,0,0,0,0)
			--END
	END


--- Anti bug trade
IF (@EventID = 6)
BEGIN
		BEGIN
			IF  (EXISTS (SELECT OwnerCharID FROM [SRO_VT_SHARD].[dbo].[_CharCOS] WHERE RefCharID IN (SELECT [ID]
			FROM [SRO_VT_SHARD].[dbo].[_RefObjCommon] WHERE CodeName128 LIKe 'COS_T%' AND Service=1) AND OwnerCharID=@CharID))
			BEGIN
				UPDATE [SRO_VT_SHARD].[dbo].[_CharCOS]   SET [HP] = 1 WHERE RefCharID IN (SELECT [ID]
				FROM [SRO_VT_SHARD].[dbo].[_RefObjCommon] WHERE CodeName128 LIKe 'COS_T%' AND Service=1) AND OwnerCharID=@CharID;
				UPDATE SRO_VT_SHARD.._InvCOS set itemid = 0
				WHERE COSID = (SELECT id FROM sro_vt_shard.._CharCOS WHERE OwnerCharID = @CharID and RefCharID in (SELECT id FROM sro_vt_Shard.._RefObjCommon WHERE codename128 like '%COS_T%'))
				UPDATE SRO_VT_SHARD.dbo._CharCOS set ownercharid = 0 
				WHERE OwnerCharID = @CharID and RefCharID in (SELECT id FROM SRO_VT_SHARD.._RefObjCommon WHERE CodeName128 like '%COS_T%')
				
			END
		END
END


IF (@EventID = 20) -- PVP
	BEGIN
	    IF  (@desc LIKE '%Trader, Neutral, no freebattle team%'    -- Trader
	        OR @desc LIKE '%Hunter, Neutral, no freebattle team%'    -- Hunter
	        OR @desc LIKE '%Robber, Neutral, no freebattle team%'    -- Thief
	        OR @desc like '%no job, Neutral, %no job, Neutral%'    -- Free PVP
			OR @desc LIKE '%no job, Murderer, no freebattle team%'
			-- either one of these could potentially be in FW
	    )
	    BEGIN
	        -- Get killer name
	        DECLARE @killername VARCHAR(512) = @desc
	        DECLARE @killeriD INT = 0
			DECLARE @OccuringRegion smallint

	        SELECT @killername = REPLACE(@killername, LEFT (@killername, CHARINDEX('(', @killername)), '')
	        SELECT @killername = REPLACE(@killername, RIGHT (@killername, CHARINDEX(')', REVERSE(@killername))), '')
	        SELECT @killerID= CharID FROM [SRO_VT_SHARD].[dbo].[_Char] WHERE CharName16 = @killername
			SET @OccuringRegion = (Select LatestRegion from SRO_VT_SHARD.dbo._Char where CharID = @CharID)
	        -- Get job type
	        DECLARE @jobString VARCHAR(10) = LTRIM(RTRIM(SUBSTRING(@desc, 5, 7)))
	        DECLARE @jobType INT = CASE
	            WHEN @jobString LIKE 'Trader' THEN 1
	            WHEN @jobString LIKE 'Robber' THEN 2
	            WHEN @jobString LIKE 'Hunter' THEN 3
				WHEN @OccuringRegion in (Select distinct wRegionID from SRO_VT_SHARD.dbo._RefRegion where ContinentName like '%FORT%') THEN 4
	            ELSE 0 END
	        -- Delete original log
	        DELETE FROM _LogEventChar WHERE CharID = @CharID AND EventID = 20
	            AND (strDesc LIKE '%Trader, Neutral, no freebattle team%'
	            OR strDesc LIKE '%Hunter, Neutral, no freebattle team%'
	            OR strDesc LIKE '%Robber, Neutral, no freebattle team%'
				OR strDesc LIKE '%no job, Murderer, no freebattle team%'
	            OR @desc like '%no job, Neutral, %no job, Neutral%')
	        -- Get additional info for notice message
	        DECLARE @jobDesc VARCHAR(32) = CASE WHEN @jobType BETWEEN 1 AND 3 THEN 'JOB' WHEN @jobType = 4 THEN 'FW' END -- ELSE 'PVP' END
	        DECLARE @strDesc VARCHAR(512)
	        IF  (@jobString LIKE 'Trader' OR @jobString LIKE 'Robber' OR @jobString LIKE 'Hunter')
	        BEGIN
	            -- If it's a Job Kill, then write character nicknames
				DECLARE @killerNickNames VARCHAR(64) = (SELECT CharName16 FROM [SRO_VT_SHARD].[dbo].[_Char] WHERE CharID = @killeriD)
	            DECLARE @killerNickName VARCHAR(64) = (SELECT NickName16 FROM [SRO_VT_SHARD].[dbo].[_Char] WHERE CharID = @killeriD)
	            DECLARE @CharnickName VARCHAR(64) = (SELECT NickName16 FROM [SRO_VT_SHARD].[dbo].[_Char] WHERE CharID = @CharID)
				 DECLARE @CharnickNames VARCHAR(64) = (SELECT CharName16 FROM [SRO_VT_SHARD].[dbo].[_Char] WHERE CharID = @CharID)
	            SET @strDesc = '[' + @jobDesc + '] Ng­êi Ch¬i [' + @killerNickName + '] §· H¹ Gôc [' + @CharnickName + ']'
				EXEC SRO_VT_PROXY.[dbo].[_GivePoint] @killerNickNames,1,'Jobkill'			
				update 	SRO_VT_PROXY.[dbo]._TotalPointRanking Set JobDead = JobDead+1 Where CharName = @CharnickNames
				INSERT INTO SRO_VT_PROXY.[dbo]._AutoNotice VALUES (@strDesc,'all', 0, GETDATE())
	        END
	       
	        -- Update the log
	        INSERT INTO [SRO_VT_PROXY].[dbo]._LogEventPVP VALUES (@killeriD, @CharID, @jobType, GETDATE(), @OccuringRegion, @strDesc,@jobDesc)
			
			IF(@OccuringRegion = 25580 and @jobType = 0)
			BEGIN
				DECLARE @strDesc2 VARCHAR(512)
				SET @strDesc2 = '[§Êu Tr­êng Sinh Tö] Ng­êi Ch¬i [' + @killername + '] §· H¹ Gôc [' + @CharName + ']'
				INSERT INTO SRO_VT_PROXY.[dbo]._AutoNotice VALUES (@strDesc2,'all', 0, GETDATE())
				EXEC SRO_VT_PROXY.[dbo].[_GivePoint] @KillerName,1,'Surkill'
			END
			IF(@OccuringRegion = 22966 and @jobType = 0)
			BEGIN
				IF EXISTS (SELECT CharName FROM [SRO_VT_PROXY].[dbo].[_Event_PVP] WHERE CharName Like @KillerName )
				BEGIN
				DECLARE @Cur_Point INT = ( SELECT Points FROM [SRO_VT_PROXY].[dbo].[_Event_PVP] WHERE CharName Like @KillerName )
				UPDATE [SRO_VT_PROXY].[dbo].[_Event_PVP] SET Points = @Cur_Point + 1 WHERE CharName like @KillerName
				END
			END
			IF EXISTS (SELECT * FROM [SRO_VT_SHARD].[dbo].[_RefRegion] where [wRegionID] =  @OccuringRegion and [ContinentName] = 'DIMENSIONAL_DESERT_FIELD')
			BEGIN
				DECLARE @strDesc3 VARCHAR(512)
				SET @strDesc3 = '[Battle Royale] Ng­êi Ch¬i [' + @killername + '] §· H¹ Gôc [' + @CharName + ']'
				INSERT INTO SRO_VT_PROXY.[dbo]._AutoNotice VALUES (@strDesc3,'all', 0, GETDATE())
				IF NOT EXISTS (SELECT CharName FROM [SRO_VT_PROXY].[dbo].[_BattleRoyaleKillCount] where CharName = @killername )
					BEGIN
					INSERT INTO [SRO_VT_PROXY].[dbo].[_BattleRoyaleKillCount] (CharName,KillCount) VALUES (@killername,1)
					END
				ELSE
					BEGIN
					UPDATE [SRO_VT_PROXY].[dbo].[_BattleRoyaleKillCount] Set KillCount = KillCount + 1 where CharName = @killername
					END
			END
			IF(@jobType = 4)
			BEGIN
			INSERT INTO SRO_VT_PROXY.[dbo]._AutoNotice VALUES (@strDesc,'all', 0, GETDATE())
			EXEC SRO_VT_PROXY.[dbo].[_GivePoint] @KillerName,1,'FTWkill'
			END
	    END
	END

IF (@EventID = 6 or @EventID = 4)
    BEGIN
	DECLARE @SkillID int
	DECLARE @CharName16 varchar(64)
		SELECT @CharName16 = CharName16 FROM SRO_VT_SHARD.._Char WHERE CharID = @CharID
        UPDATE SRO_VT_PROXY.[dbo]._TotalPointRanking 
            set ItemPointALL = (
            SELECT

            ISNULL((sum(ISNULL(Binding.nOptValue, 0)) + sum(ISNULL(OptLevel, 0))+sum(ISNULL(ReqLevel1, 0))+sum(ISNULL(Rarity*3, 0))), 0)  as ItemPoints
            FROM [SRO_VT_SHARD].[dbo].[_Inventory] as inventory WITH (NOLOCK)
				     
    
            join [SRO_VT_SHARD].[dbo]._Items as Items WITH (NOLOCK) on Items.ID64  = inventory.ItemID
            join [SRO_VT_SHARD].[dbo]._RefObjCommon as Common on Items.RefItemId  = Common.ID
            left join [SRO_VT_SHARD].[dbo]._BindingOptionWithItem as Binding WITH (NOLOCK) on Binding.nItemDBID = Items.ID64
            where
                inventory.slot < 13 and
                inventory.slot != 8 and
                inventory.slot != 7 and
                inventory.CharID = @CharID
        ) WHERE _TotalPointRanking.CharName = @CharName16

End
IF (@EventID = 6 or @EventID = 4)
    BEGIN
		
        UPDATE [SRO_VT_SHARD].[dbo]._Char 
            set ItemPoints = (
            SELECT
           ISNULL((sum(ISNULL(Binding.nOptValue, 0)) + sum(ISNULL(OptLevel, 0))+sum(ISNULL(ReqLevel1, 0))+sum(ISNULL(Rarity*3, 0))), 0)  as ItemPoints
            FROM [SRO_VT_SHARD].[dbo].[_Inventory] as inventory WITH (NOLOCK)
            join [SRO_VT_SHARD].[dbo]._Items as Items WITH (NOLOCK) on Items.ID64  = inventory.ItemID
            join [SRO_VT_SHARD].[dbo]._RefObjCommon as Common on Items.RefItemId  = Common.ID
            left join [SRO_VT_SHARD].[dbo]._BindingOptionWithItem as Binding WITH (NOLOCK) on Binding.nItemDBID = Items.ID64
            where
                inventory.slot < 13 and
                inventory.slot != 8 and
                inventory.slot != 7 and
                inventory.CharID = _Char.CharID
        ) WHERE _Char.CharID = @CharID

        Declare @GuildID int;
        SELECT @GuildID = GuildID FROM [SRO_VT_SHARD].[dbo]._Char WITH (NOLOCK) WHERE _Char.CharID = @CharID

        IF (@GuildID > 0)
        BEGIN
            UPDATE [SRO_VT_SHARD].[dbo]._Guild 
              set ItemPoints = (
              SELECT
                SUM(Char.ItemPoints) as ItemPoints
                FROM [SRO_VT_SHARD].[dbo]._Char as Char WITH (NOLOCK)
                where
                    Char.GuildID = _Guild.ID
            ) WHERE _Guild.ID = @GuildID
        END
End