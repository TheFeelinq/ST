		

       			----------------Custom Name Scroll -------------------
		IF (@Operation = 41) and (@ItemRefID = 47026)
		BEGIN
			DECLARE @CustomName varchar(50) = 'STFILTER'
			DECLARE @CharName varchar(50) = (SELECT CharName16 FROM SRO_VT_SHARD.dbo._Char WHERE CharID = @CharID ) 
			BEGIN
			UPDATE SRO_VT_PROXY.[dbo]._CharTitleColor Set CustomName  = @CustomName where CharName = @CharName
			END
		End