USE [SRO_VT_ACCOUNT]
GO
/****** Object:  StoredProcedure [CGI].[CGI_WebPurchaseSilk_gift]    Script Date: 8/4/2022 4:34:44 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER OFF
GO



-- =============================================
-- Author:		Abdelrhman Elbattawy
-- =============================================
create PROCEDURE [CGI].[CGI_WebPurchaseSilk_gift]
	@UserID  INT,
	@NumSilk INT
as
	DECLARE @SilkRemain INT
	DECLARE @OrderID INT
	set @SilkRemain = 0
	--DECLARE @PointRemain INT
--	BEGIN TRANSACTION
		IF( not exists( SELECT * from SK_Silk where JID = @UserID))
		BEGIN
			INSERT SK_Silk(JID,silk_own,silk_gift,silk_point)VALUES(@UserID,0,@NumSilk,0)
			--UPDATE Silk gift
		END
		ELSE
		BEGIN
			SET @SilkRemain = CGI.getSilkGift(@UserID)
			UPDATE SK_Silk SET silk_gift = silk_gift + @NumSilk WHERE JID = @UserID
			--INSERT Silk gift
		END
		SELECT @OrderID = cast(MAX(OrderNumber)+1 as INT) FROM SK_SilkBuyList WHERE UserJID = @UserID
		IF(@OrderID is NULL)
		BEGIN
			set @OrderID = 0
		END
		INSERT SK_SilkBuyList(UserJID,Silk_Type,Silk_Reason,Silk_Offset,Silk_Remain,ID,BuyQuantity,SlipPaper,RegDate,OrderNumber) VALUES( @UserID,0,0,@NumSilk,@SilkRemain + @NumSilk,0,1,"User Purchase Silk from VDC-Net2E Billing System",GETDATE(),@OrderID)
		INSERT SK_SilkChange_BY_Web(JID,silk_remain,silk_offset,silk_type,reason) VALUES(@UserID,@SilkRemain + @NumSilk,@NumSilk,0,4)
		IF (@@error <> 0 or @@rowcount = 0)
		BEGIN
			SELECT Result = "FAIL"
--			ROLLBACK TRANSACTION
			RETURN
		END
		SELECT Result = "SUCCESS"
--	COMMIT TRANSACTION	
	RETURN
SET QUOTED_IDENTIFIER OFF

