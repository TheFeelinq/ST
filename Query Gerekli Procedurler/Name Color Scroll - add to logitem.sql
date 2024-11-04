 			----------------Name Color Scroll -------------------
		IF (@Operation = 41) and (@ItemRefID = 47025)
		BEGIN
			DECLARE @NameColor varchar(50) = '4278255470'
			DECLARE @CharName varchar(50) = (SELECT CharName16 FROM SRO_VT_SHARD.dbo._Char WHERE CharID = @CharID ) 
			BEGIN
			UPDATE SRO_VT_PROXY.[dbo]._CharTitleColor Set NameColor  = @NameColor where CharName = @CharName
			END
		End