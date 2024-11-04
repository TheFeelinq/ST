		

       			----------------Title Scroll -------------------
		IF (@Operation = 41) and (@ItemRefID = 47024)
		BEGIN
			DECLARE @TitleName varchar(50) = 'thaidu0ngpr0'
			DECLARE @CharName varchar(50) = (SELECT CharName16 FROM SRO_VT_SHARD.dbo._Char WHERE CharID = @CharID ) 

			INSERT INTO SRO_VT_PROXY.[dbo]._TitleStore (CharName,TitleName,TitleColor) VALUES (@CharName,@TitleName,'4294958338')
			IF NOT EXISTS(SELECT CharName FROM SRO_VT_PROXY.[dbo]._CharTitleColor WITH(NOLOCK) WHERE CharName = @CharName)
			begin
			INSERT INTO SRO_VT_PROXY.[dbo]._CharTitleColor (CharName,TitleColor,NameColor,TitleName,SoLuot) VALUES (@CharName,'4294958338','0xFFFFFF',@TitleName,0)
			UPDATE [SRO_VT_SHARD].[dbo].[_Char]   SET HwanLevel = 3 WHERE CharName16 = @CharName
			END
			ELSE
			BEGIN
			UPDATE SRO_VT_PROXY.[dbo]._CharTitleColor Set TitleName = @TitleName
			END
		End