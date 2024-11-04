USE [SRO_VT_PROXY]
GO
/****** Object:  StoredProcedure [dbo].[_OnUniqueEntered]    Script Date: 12/4/2022 3:47:52 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
ALTER PROCEDURE [dbo].[_OnUniqueEntered]
	-- Add the parameters for the stored procedure here
	@Name varchar(128)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

    -- Insert statements for procedure here
	
	DECLARE @UniqueID int = (SELECT ID FROM SRO_VT_SHARD.dbo._RefObjCommon WHERE CodeName128 = @Name ) 
	IF EXISTS(SELECT UniqueName FROM SRO_VT_PROXY.._LogUniqueKills WITH (NOLOCK) WHERE UniqueName = @Name)
		BEGIN
			Update _LogUniqueKills set KillerName = '<None>',[State] = 1 , KilledTime = GETDATE() where UniqueName = @Name
		END
	ELSE
		BEGIN
		INSERT INTO _LogUniqueKills(KillerName, UniqueName,KilledTime,State,UniqueID) VALUES('<None>',@Name, GETDATE(),1,@UniqueID)
		END

	INSERT INTO _LogUniqueEntered(Name, Time) VALUES(@Name, GETDATE())
	IF EXISTS(SELECT UniqueName FROM SRO_VT_PROXY.._LogUniqueKilled WITH (NOLOCK) WHERE UniqueName = @Name)
		BEGIN
			delete SRO_VT_PROXY.._LogUniqueKilled WHERE UniqueName = @Name
		END
END
