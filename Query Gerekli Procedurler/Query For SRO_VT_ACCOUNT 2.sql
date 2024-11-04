USE [SRO_VT_ACCOUNT]
GO
/****** Object:  StoredProcedure [CGI].[CGI_WebPurchaseSilk]    Script Date: 8/4/2022 11:57:23 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER OFF
GO

ALTER PROCEDURE [CGI].[CGI_WebPurchaseSilk]
	@OrderID VARCHAR(25),
	@UserID   VARCHAR(25),
	@PkgID   INT,
	@NumSilk INT,
	@Price INT
as
	DECLARE @UserJID INT
	DECLARE @SilkRemain INT
	--DECLARE @PointRemain INT
	set @OrderID = (Select Max(cast(OrderNumber as int)) + 1 from SRO_VT_ACCOUNT.dbo.SK_SilkBuyList)

	SET @UserJID = CGI.getUserJID(@UserID)
	IF( @UserJID >= 0)
	    BEGIN
		IF( not exists( SELECT OrderNumber from SK_SilkBuyList where OrderNumber = @OrderID))
		BEGIN
			BEGIN TRANSACTION
                           IF( not exists( SELECT * from SK_Silk where JID = @UserJID))
				BEGIN
					INSERT SK_Silk(JID,silk_own,silk_gift,silk_Point)VALUES(@UserJID,@NumSilk,0,0)
					--INSERT Silk Own
					INSERT SK_SilkBuyList(UserJID,Silk_Type,Silk_Reason,Silk_Offset,Silk_Remain,ID,BuyQuantity,OrderNumber,SlipPaper,RegDate) VALUES( @UserJID,0,0,@NumSilk,@NumSilk,@PkgID,1,@OrderID,"User Purchase Silk from VDC-Net2E Billing System",GETDATE())
					INSERT SK_SilkChange_BY_Web(JID,silk_remain,silk_offset,silk_type,reason) VALUES(@UserJID,@NumSilk,@NumSilk,0,0)
				END
			    ELSE
				BEGIN
					SET @SilkRemain = CGI.getSilkOwn(@UserJID)
					UPDATE SK_Silk SET silk_own = silk_own + @NumSilk WHERE JID = @UserJID
					--INSERT Silk Own		
					
					INSERT SK_SilkBuyList(UserJID,Silk_Type,Silk_Reason,Silk_Offset,Silk_Remain,ID,BuyQuantity,OrderNumber,SlipPaper,RegDate) VALUES( @UserJID,0,0,@NumSilk,@SilkRemain + @NumSilk,@PkgID,1,@OrderID,"User Purchase Silk from VDC-Net2E Billing System",GETDATE())			
					INSERT SK_SilkChange_BY_Web(JID,silk_remain,silk_offset,silk_type,reason) VALUES(@UserJID,@SilkRemain + @NumSilk,@NumSilk,0,0)
				END
			IF (@@error <> 0 or @@rowcount = 0)
				BEGIN
					SELECT Result = "FAIL"
					ROLLBACK TRANSACTION
					RETURN
				END
			SELECT Result = "SUCCESS"
			COMMIT TRANSACTION	
			RETURN
		   END
		ELSE --else if order
		   BEGIN
			SELECT Result = "ORDEREXIST"
		   END    
	    END
	ELSE
		BEGIN
			SELECT Result = "NOUSER"
			RETURN
		END


		
		
SET QUOTED_IDENTIFIER OFF

