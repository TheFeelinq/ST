USE [SRO_VT_PROXY]
GO
/****** Object:  StoredProcedure [dbo].[_OnUniqueKilled]    Script Date: 12/4/2022 3:48:23 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
ALTER PROCEDURE [dbo].[_OnUniqueKilled]
	-- Add the parameters for the stored procedure here
	@UniqueName varchar(128),
	@KillerName varchar(32)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

	DECLARE @UniqueID int = (SELECT ID FROM SRO_VT_SHARD.dbo._RefObjCommon WHERE CodeName128 = @UniqueName ) 
	IF EXISTS(SELECT UniqueName FROM SRO_VT_PROXY.._LogUniqueKills WITH (NOLOCK) WHERE UniqueName = @UniqueName)
		BEGIN
			Update _LogUniqueKills set KillerName = @KillerName,[State] = 0 , KilledTime = GETDATE() where UniqueName = @UniqueName
		END
	ELSE
		BEGIN
		INSERT INTO _LogUniqueKills(KillerName, UniqueName,KilledTime,State,UniqueID) VALUES(@KillerName,@UniqueName, GETDATE(),0,@UniqueID)
		END

    -- Insert statements for procedure here
	INSERT INTO _LogUniqueKilled(UniqueName, KillerName, Time) 
		VALUES(@UniqueName, @KillerName, GETDATE())
		IF EXISTS(SELECT [Name] FROM SRO_VT_PROXY.._LogUniqueEntered WITH (NOLOCK) WHERE [Name] = @UniqueName)
		BEGIN
			delete SRO_VT_PROXY.._LogUniqueEntered WHERE [Name] = @UniqueName
		END
END
