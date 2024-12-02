USE GlobalToyz
go

/* creating required data types */
execute sp_addtype id      ,'char(6)' ,'NOT NULL'
raiserror('Now at the Create Table section ....',0,1)
Go
raiserror('Creating Table Category....',0,1)
create table Category
(
	cCategoryId	char(3) constraint ct_pk primary key,
	cCategory	char(20) not null,
	vDescription	varchar(100)
)
go
raiserror('Creating Table Wrapper....',0,1)
create Table Wrapper
(
	cWrapperId 	char(3)	constraint w_id primary key clustered,
	vDescription	varchar(20),
	mWrapperRate	money not null,
	imPhoto		image null,
	vWrapperImgPath varchar(50) null

)
go
raiserror('Creating Table ToyBrand....',0,1)
create table ToyBrand
(
	cBrandId	char(3) constraint TB_pk primary key,
	cBrandName	char(20) not null,
)
go
/***************************/
raiserror('Creating Table Country....',0,1)
create table Country
(
	cCountryId	char(3) constraint c_pk primary key,
	cCountry		char(25) not null,
)
go
raiserror('Creating Table ShippingMode....',0,1)
create table ShippingMode
(
	cModeId		char(2) constraint spm_pk primary key,
	cMode 		char(25) not null,
	iMaxDelDays	int,
)
go
raiserror('Creating Table ShippingRate....',0,1)
create table ShippingRate
(
	cCountryID	char(3) references Country(cCountryId) ,
	cModeId 		char(2) references  ShippingMode(cModeId),
	mRatePerPound	money not null,
	constraint SR_PRK primary key(cCountryID,cModeId)
/* need to create composite primary  key */
)
raiserror('Creating Table Shopper....',0,1)
create table Shopper
(
	cShopperId 	char(6)	constraint s_id primary key CLUSTERED,
	cPassword 	char(10) not null,
	
	vFirstName 	varchar(20) not null,
	vLastName 	varchar(20) not null,
	vEmailId	varchar(40) not null,
	vAddress 	varchar(40) not null,
	cCity 		char(15) not null,
	cState 		char(15) not null,
	cCountryId 	char(3) references Country(cCountryId),
	cZipCode	char(10), /*  check(cZipCode like '[0-9][0-9][0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]'), */
	cPhone 		char(15) not null ,
	cCreditCardNo 	char(16) not null,
	vCreditCardType 	varchar(15) not null,
	dExpiryDate 	datetime 
)
go

raiserror('Creating Table Toys....',0,1)
/* toys table */
create table Toys
(
	cToyId		char(6)  check(cToyId like('[0-9][0-9][0-9][0-9][0-9][0-9]') )
				constraint t_id primary key clustered,
				
	vToyName	varchar(20) not null,
	vToyDescription	varchar(250),
	cCategoryId	char(3) references Category(cCategoryId) ,
	mToyRate	money not null,
	cBrandId	char(3)references ToyBrand(cBrandId),
	imPhoto 	image,
	siToyQoh	smallint not null,
	siLowerAge	smallint not null,
	siUpperAge	smallint not null,
	siToyWeight	smallint,
	vToyImgPath	varchar(50) null

)
go
/*                         */
/* ShoppingCart */
raiserror('Creating Table ShoppingCart....',0,1)
create table ShoppingCart
(
	cCartId 	char(6) not null, 
	cToyId		char(6)REFERENCES Toys(cToyId),/* foreign key to Toys table */
	siQty		smallint not null,
	constraint SCHP_PK primary key(cCartId,cToyId)
)
go

/***********************/

/* Order */
raiserror('Creating Table Order....',0,1)
create table Orders
(
	cOrderNo 	char(6) constraint CO_PK Primary key, 
	dOrderDate 	datetime not null,
	cCartId		char(6) not null, 
	cShopperId	char(6) not null references Shopper(cShopperId),
	cShippingModeId	char(2) null references ShippingMode(cModeId),
	mShippingCharges money  null,
	mGiftWrapCharges	money null,
	cOrderProcessed	char null ,
	mTotalCost	money  null,
	dExpDelDate	DateTime null
)
go


/* OrderDetail table */

raiserror('Creating Table OrderDetails....',0,1)
create table OrderDetail
(
	cOrderNo 	char(6) references Orders(cOrderNo),
	cToyId 		char(6)  references toys(cToyId),
	siQty 		smallint  not null,
	cGiftWrap	char null, 
	cWrapperId	char(3) references Wrapper(cWrapperId) null,
	vMessage	varchar(256) null,
	mToyCost        money null,
		constraint z_key primary key(cOrderNo,cToyId)
)
go

/* shipping mode */

/* Shipment */
raiserror('Creating  Shippment....',0,1)
create table Shipment
(
	cOrderNo		char(6)  REFERENCES Orders(cOrderNo) constraint SHP_PK primary key,  
	dShipmentDate	datetime null, /* cannot be before order date */
	cDeliveryStatus	char null, 
	dActualDeliveryDate datetime null
)
go
/* Recipient table */
raiserror('Creating Table Recipient....',0,1)
create table Recipient
(
	cOrderNo		char(6) REFERENCES Orders(cOrderNo) constraint RCP_PK primary key, /* foreign key to order table */
	vFirstName 		varchar(20) not null,
	vLastName 		varchar(20) not null,
	vAddress		varchar(20) not null,
	cCity 		        char(15) not null,
	cState			char(15) not null,
	cCountryId	char(3) references Country(cCountryId),
	cZipCode		char(10) check(cZipCode like '[0-9][0-9][0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]'),
	cPhone		char(15)
)
go


/* pick of the month */
raiserror('Creating Table PickOfMonth....',0,1)
create table PickOfMonth
(
	cToyId 		char(6)REFERENCES Toys(cToyId), /* foreign key to toy table */
	siMonth		smallint,
	iYear		int,
	iTotalSold	int,
	constraint POM_PK primary key(cToyId,siMonth,iYear)
)
go


/*****************************************************/
-- Populating data into the tables
/********************/
insert into Category values('001','Activity','Activity toys encourage the childs social skills and interest in the world around them.')
insert into Category values('002','Dolls','A wide range of dolls from all the leading brands.')
insert into Category values('003','Arts And Crafts','Encourage children to create masterpieces with these incredible craft kits.')
insert into Category values('004','Games','A complete range of new and classic games.')
insert into Category values('005','Cars N Racing','Models of all current and vintage cars.')
insert into Category values('006','Pretend Play','These games can play an important part in the childs development.') /* Children can use these tools they need to play out their dreams.') */
insert into Category values('007','Model Kits','Models to build planes, cars, ships and much more.')
insert into Category values('008','Infant','Colorful, interactive toys for babies.')
insert into Category values('009','Stuffed Toys','Teddy bears, monkeys and many more soft toys.')
insert into Category values('010','Learning','Designed to make learning so much fun that children will forget they are learning at the same time')
insert into Category values('011','Science and Nature','Toys which encourage children to explore the world around them.')
insert into Category values('012','Musical toys','These toys generate music, sound and songs too.')
insert into Category values('013','Electronic','These are electronic toys, which run using batteries.')
insert into Category values('014','Puppets','These are puppet toys.')
insert into Category values('015','Trains','These trains will be the pride of any railway system.')
insert into Category values('016','Construction Toys','Bricks, building and other toys the will encourage children to build model houses and buildings.')
/* data for wrapper  */
insert into Wrapper values('001','Geckos',1,null,null)
insert into Wrapper values('002','Baby blocks',1.25,null,null)
insert into Wrapper values('003','Stars',1.50,null,null)
insert into Wrapper values('004','Bubbles',2,null,null)
insert into Wrapper values('005','Sesame street',1.5,null,null)
insert into Wrapper values('006','Moon',2.25,null,null)
insert into Wrapper values('007','Sea',1,null,null)
insert into Wrapper values('008','Sky',1,null,null)

/*        toy brand  */
INSERT INTO ToyBrand values('001','Bobby ')
INSERT INTO ToyBrand values('002','Frances-Price')
INSERT INTO ToyBrand values('003','The Bernie Kids')
INSERT INTO ToyBrand values('004','Largo')
INSERT INTO ToyBrand values('005','LAMOBIL')
INSERT INTO ToyBrand values('006','Crazy World')
INSERT INTO ToyBrand values('007','Brevet')
INSERT INTO ToyBrand values('008','Darden')

/* data for country  */
insert into Country values('001','United states of America')
insert into Country values('002','Albania')
insert into Country values('003','Andorra')
insert into Country values('004','Argentina')
insert into Country values('005','Austria')
insert into Country values('006','Bangladesh')
insert into Country values('007','Belgium')
insert into Country values('008','Bosnia & Herzegovina')
insert into Country values('009','Bulgaria')
insert into Country values('010','Czech Republic')
insert into Country values('011','Denmark')
insert into Country values('012','Yugoslavia ')
insert into Country values('013','France')
insert into Country values('014','Gibraltar')
insert into Country values('015','Greece')
insert into Country values('016','Georgia')
insert into Country values('017','Croatia')
insert into Country values('018','Estonia')
insert into Country values('019','Iceland')
insert into Country values('020','Italy')
insert into Country values('021','Israel')
insert into Country values('022','India')
insert into Country values('023','Cyprus')
insert into Country values('024','Russia')
insert into Country values('025','Liechtenstein')
insert into Country values('027','Lithuania')
insert into Country values('028','Luxembourg')
insert into Country values('030','Malta')
insert into Country values('031','Moldova')
insert into Country values('032','Monaco')
insert into Country values('033','Netherlands')
insert into Country values('034','Norway')
insert into Country values('035','Poland')
insert into Country values('036','Portugal')
insert into Country values('037','Romania')
insert into Country values('038','San Marino')
insert into Country values('039','Slovak Republic')
insert into Country values('040','Slovenia')
insert into Country values('041','Finland')
insert into Country values('042','Spain')
insert into Country values('043','Switzerland')
insert into Country values('044','Turkey')
insert into Country values('045','Ukraine')
insert into Country values('046','Hungary')
insert into Country values('047','Germany')
insert into Country values('048','Sweden')
insert into Country values('049','Latvia')
/* data into shippingmode  */
insert into ShippingMode values('01','Standard Shipping',4)
insert into ShippingMode values('02','World Mail',3)
insert into ShippingMode values('03','International Priority',1)
/* shipping rate  */
insert into ShippingRate values('001','01',2)
insert into ShippingRate values('001','02',4)
insert into ShippingRate values('001','03',10)
insert into ShippingRate values('002','01',03)
insert into ShippingRate values('002','02',06)
insert into ShippingRate values('002','03',10)
insert into ShippingRate values('003','01',04)
insert into ShippingRate values('003','02',06)
insert into ShippingRate values('003','03',12)
insert into ShippingRate values('004','01',04)
insert into ShippingRate values('004','02',08)
insert into ShippingRate values('004','03',12)
insert into ShippingRate values('005','01',04)
insert into ShippingRate values('005','02',08)
insert into ShippingRate values('005','03',12)
insert into ShippingRate values('006','01',04)
insert into ShippingRate values('006','02',08)
insert into ShippingRate values('006','03',12)
insert into ShippingRate values('007','01',04)
insert into ShippingRate values('007','02',06)
insert into ShippingRate values('007','03',10)
insert into ShippingRate values('008','01',04)
insert into ShippingRate values('008','02',05)
insert into ShippingRate values('008','03',08)
insert into ShippingRate values('009','01',10)
insert into ShippingRate values('009','02',12)
insert into ShippingRate values('009','03',15)
insert into ShippingRate values('010','01',10)
insert into ShippingRate values('010','02',12)
insert into ShippingRate values('010','03',15)

/*data into shopper  */
insert into shopper values('000001','angels','Angela','Smith','angelas@qmail.com','16223 Radiance Court','Woodbridge','Virginia','001','22191','227-2344','6947343412896785','Master Card','08/09/2021')
insert into shopper values('000002','guide','Barbara','Johnson','barbaraj@speedmail.com','227 Beach Ave.','Sunnyvale','California','001','94087-1147','123-5673','5345146765854356','Master Card','04/10/2021')
insert into shopper values('000003','youbet','Betty','Williams','bettyw@dpeedmil.cm','1 Tread Road','Virginia Beach','Varginia','001','23455','458-3299','4747343412896785','Visa Card','12/12/2021')
insert into shopper values('000004','credit','Carol','Jones','carolj@qmail.com','765 - Furling Road Apt 112  ','Boone','North Carolina','001','28607','678-4544','6344676854335436','Visa Card','10/12/2021')
insert into shopper values('000005','prepare','Catherine','Roberts','catheriner@qmail.com','5508 Aquiline Court','San Jose','California','001','95123','445-2256','3756784562869963','Master Card','09/10/2021')
insert into shopper values('000006','Char','Charles','Brown','charlesb@speedmail.com','7822 S. Glitzy Avenue ','Maitland','Florida','001','32751','225-6678','3454678545443344','Visa Card','10/09/2021')
insert into shopper values('000007','chris','Christopher','Davis','Christopherd@qmail.com','4896 11th ST  ','Hill Avenue','Utah','001','84056-5410','556-9087','7899887675443322','Visa Card','10/02/2021')
insert into shopper values('000008','mills','Cynthia','Miller','cynthiam@qmailcom','98066 Weary Storm Street','Moon Park ','California','001','93021-2930','422-5688','2345566576879900','Master Card','08/09/2021')
insert into shopper values('000009','gotcha','Daniel','Wilson','danielw@speedmail.com','4642 Peripheral Drive  ','Brecksville','Ohio','001','44141','454-2246','2345467890986745','Visa Card','11/02/2021')
insert into shopper values('000010','bingo','David','Moore','davidm@qmail.com','8808 Joviality Drive   ','San Ramon','California','001','94583','982-5577','2343556678799674','Visa Card','11/12/2021')
insert into shopper values('000011','chubby','Deborah','Taylor','deboraht@qmail.com','2199- Fairfax Drive ','Libertyville','Illinois','001','60048','889-2235','2345468798078563','Master Card','11/23/2021')
insert into shopper values('000012','smile','Donna','Anderson','Donnaa@speedmail.com ','7930 Orange St. ','Las Vegas','Nevada','001','89117','845-2323','2314345676568766','Visa Card','11/24/2021')
insert into shopper values('000013','benhur','Dorothy','Thomas','dorthyt@speedmail.com','678 East 56th Street- #12','New York','New York','001','10009','696-2278','8765435456678754','Visa Card','12/03/2021')
insert into shopper values('000014','benjy','Elizabeth','Jackson','elizabethj@qmail.com','598 Apex Avenue #2','Saint Paul ','Minnesota','001','55102','545-9078','4576544354567542','Visa Card','10/06/2021')
insert into shopper values('000015','sundance','Frances','Turner         ','francest@speedmail.com','2562 Eastwood  ','Denton','Texas','001','76205-5922','878-6670','5676879007565452','Master Card','08/30/2021')
insert into shopper values('000016','bopeep','Helen','White','helenw@spedmail.com','Fleet Street','Point Pleasant','Pennsylvania','001','18950 ','585-7796','4564564564564565','Visa Card','10/10/2021')
insert into shopper values('000017','momma','James','Harris',' helenw@spedmail.com','3456 Mt. Regale Drive  ','1509 Alexandria','Virginia','001','22303-2541','335-6678','4657567545344544','Master Card','10/31/2021')
insert into shopper values('000018','grumpy','Jennifer','Martin','jenniferm@qmail.com','9812  76th Street  ','Brooklyn','Maryland','001','21225','569-7789','9775445343233443','Visa Card','09/01/2021')
insert into shopper values('000019','patch','Jessica','Thompson','jessicat@speedmail.com','565 Pebble St. ','Arlington','Texas','001','76014','445-6797','9766545343233455','Master Card','09/19/2021')
insert into shopper values('000020','sunshine','John','Garcia','johng@qmail.com','2234 B King Henry Drive ','Harrisburg','Pennsylvania','001','17109','521-9095','8764554334534567','Master Card','09/13/2021')
insert into shopper values('000021','good','Joseph','Martinez','josephm@qmail.com','995 Rind Street ','Loma Linda','California','001','92354','456-9032','5687567567435344','Visa Card','05/31/2021')
insert into shopper values('000022','nestle','Joyce','Phillips','joycep@speedmail.com','535 Darwin Avenue ','Bridgeville','Pennsylvania','001','15017','789-6905','2345345345645656','Master Card','09/15/2021')
insert into shopper values('000023','hangon','Karen','Robinson','karenr@qmail.com','2343-A Flowers Ferry Road    ','Marietta','Georgia','001','30067','334-5568','4546575675687689','Visa Card','02/26/2020')
insert into shopper values('000024','rumble','Kimberly','Clark','kimberlyc@speedmail.com','79 Holler Valley Road ','Little Rock','Arkansas','001','72204','645-9023','2345653757898999','Master Card','05/31/2020')
insert into shopper values('000025','noddy','Laura','Rodriguez','laurar@speedmail.com','3242 Limestone','WayMarietta','Georgia','001','30062','567-3345','2345345676786543','Visa Card','03/03/2020')
insert into shopper values('000026','falcon','Linda','Lewis','lindal@qmail.com','1524 Patagonia Lane ','Plano','Texas','001','75075','459-4563','8765434523543366','Visa Card','03/14/2020')
insert into shopper values('000027','lazer','Lisa','Lee','lisal@speedmail.com','18927 Sandstone Ave N ','Seattle','Washington','001','98133','897-3345','7653534745756567','Master Card','08/30/2021')
insert into shopper values('000028','spartan','Margaret','Walker','margaretw@speedmail.com','405 SE Aden #101 ','Pullman','Washington','001','99163','567-9083','9867865434534467','Master Card','07/09/2021')
insert into shopper values('000029','zedi','Maria','Hall','Mariah@speedmail.com','936 Midland Drive ?','Rochester','New York','001','14609','345-8764','9786434564564567','Visa Card','04/06/2020')
insert into shopper values('000030','norman','Mary','Allen','marya@qmail.com','1202 Heathcliff Drive ','Urbana','Illinois','001','61801-5304','749-3096','8674564574574356','Master Card','04/23/2020')
insert into shopper values('000031','denice','Michael','Young','michaely@speedmail.com','440 Allens Trail' ,'Montgomery','Alabama','001','36117','560-9004','3478786786785677','Master Card','02/21/2020')
insert into shopper values('000032','kate','Michelle','Hernandez','michelleh@speedmail.com','1353 Realm Lakes ','Naperville','Illinois','001','60563','294-5385','6965753564534554','Visa Card','01/02/2020')
insert into shopper values('000033','pirate','Nancy','King','nancyk@qmail.com','429 Ash Birch Lane  ','North Andover','Massachusetts','001','01845','563-2298','3464276587468846','Master Card','01/01/2020')
insert into shopper values('000034','titanic','Patricia','Wright','patreciaw@speedmail.com','5689 Marshland Road ','Clayton','California','001','94517-1440','345-8765','3743567985785344','Master Card','02/21/2020')
insert into shopper values('000035','fire','Paul','Lopez','paull@qmail.com','13459 Campton Street ','Sherman Oaks ','California','001','91401','912-7905','4436465768677778','Master Card','03/03/2020')
insert into shopper values('000036','pizza','Richard','Hill','richardh@speedmail.com','1125 Feeder Road ','Glencoe','Illinois','001','60022','459-8749','9568765745645666','Visa Card','10/06/2021')
insert into shopper values('000037','heman','Robert','Scott','Roberts@speedmail.com','5296 Hardboard Dr ','Oakland','California','001','94618','709-5565','8678457546556555','Master Card','10/02/2021')
insert into shopper values('000038','herby','Ruth','Green','ruthg@speedmail.com','459 Ridge Road ','Mendham','New Jersey','001','07945','347-9082','9887654445423443','Visa Card','12/02/2021')
insert into shopper values('000039','superman','Sandra','Adams','Sandra@qmail.com','12454 Boggy Blvd. ','Orlando','Florida','001','32824','982-9503','7455463534636555','Master Card','04/18/2020')
insert into shopper values('000040','emerand','Sarah','Baker','sarahb@qmail.com','2394 Emerald Street ','Tarzana','California','001','91356','439-2309','8745654544323343','Visa Card','07/30/2020')
insert into shopper values('000041','hills','Sharon','Gonzalez','sharong@speedmail.com','1289 Belvedere Street  ','Hillsdale','New Jersey','001','07642-0006','230-8040','8765563434543554','Master Card','11/27/2020')
insert into shopper values('000042','apartment','Shirley','Nelson','shirlyn@speedmail.com','56700 Chain Boulevard Apartment # 899 ','Austin','Texas','001','78728','409-2387','8656554233242334','Master Card','01/27/2020')
insert into shopper values('000043','loft','Susan','Carter','susanc@speedmail.com','3478 Central St.  Loft 201  ','Dallas','Texas','001','75226','309-8056','9654323233457864','Visa Card','12/29/2021')
insert into shopper values('000044','sugar','Thomas','Mitchell','thomasm@qmail.com','2103 Ancient Fable Drive','Sugar Land ','Texas','001','77478','408-3389','8545432346765545','Visa Card','12/30/2021')
insert into shopper values('000045','lakes','William','Perez','williamp@qmail.com','987 Tetragon Avenue ','Chickasha','Oklahoma','001','73018','234-8764','8553435667455454','Visa Card','12/31/2021')
insert into shopper values('000046','trail','David','Cooper','davidc@speedmail.com','5614 Raffle Court  ','Concord','California ','001','94521','678-3458','7877654435543424','Master Card','03/14/2020')
insert into shopper values('000047','drive','Peter','Prescott','peterp@qmail.com','340 Miasma Drive','Edinboro','Pennsylvania','001','16412','890-4084','8965453446556577','Visa Card','03/13/2020')
insert into shopper values('000048','california','John','Doran','johnd@qmail.com','678 Warren Drive - Suite 2B ','Sunnyvale','California','001',' 94086','349-9152','8565456533457545','Master Card','03/14/2020')
insert into shopper values('000049','clay','Jane','Schaffer','janes@qmail.com','521?State Street','Annapolis','Maryland','001','21403','280-9999','8556543443545444','Visa Card','10/08/2021')
insert into shopper values('000050','master','Heather','Landis','heatherl@speedmail.com','1204 West Draper'   , 'Chicago','Illinois','001','60614','765-2322','7545475565655433','Master Card','10/15/2021')

/* data for toys  */
insert into toys values('000001','Robby the Whale ','A giant Blue Whale with two heavy-duty handles that allow a child to ride on its back. ','001', 8.99 ,'001',NULL,50,3,9,1,null)
insert into toys values('000002','Water Channel System ','Children enjoy playing with water.  The Water Channel System consists of 22 interchangeable pieces including a dock with moveable crane and a water wheel, which creates a current in the water and four boats','001', 33.99,'001',NULL,60,5,9,2,null)
insert into toys values('000003','Parachute and Rocket ','Step on the launch pad and the rocket is launched which sends a parachute slowly down to earth. ','001', 6.99,'003',NULL,90,7,9,1,null)
insert into toys values('000004','Super Deluge','Create artificial rainfall in your garden with this super deluge.','001', 35.99,'005',NULL,74,8,9,1,null)
insert into toys values('000005','Light Show Lamp','Build a revolving, glowing mood lamp with a set of colorful scenes. ','002', 15.99,'001',NULL,58,7,9,1,null)
insert into toys values('000006','Glass Decoration','Make your own beautiful, art work. Set includes eight paints, one paintbrush, patterns and complete instructions.','002', 12.99,'004',NULL,99,8,9,2,null)
insert into toys values('000007','Tie Dye Kit','CHECK THE ORIGINAL TOY LIST','002', 19.99,'002',NULL,76,7,9,1,null)
insert into toys values('000008','Alice in Wonderland','A huge coloring book.  ','002', 14.99,'001',NULL,82,4,8,1,null)
insert into toys values('000009','Glamorous Doll','She is ready for her acting audition in this blue denim dress and jacket. To carry her film gear, she has a video camera and red tote bag. ','002', 18.99,'001',NULL,39,6,9,2,null)

--insert into toys values('000010','Bubble Fairy Doll','You can make a little girls wishes come true with the Bubble Fairy magic bubbles! You just need to dip the magic wands into the magic solution, and then press the button on her shoe. She then spins, making lots of bubbles. The magical bubble-making solution, a dipping tray, and three bubble-making wands which snap easily onto the Bubble Fairy’s wrists are included in the kit.','002', 9.99,'002',NULL,78,4,8,1,null)
insert into toys values('000011','Sleeping Beauty Doll','Let your child enact this magical fairy tale with the Sleeping Beauty Doll. ','002', 18.99,'005',NULL,65,4,8,1,null)
insert into toys values('000012','Pet Loving Doll','A beautiful doll with a small pet puppy.','002', 10.99,'001',NULL,82,4,8,1,null)
insert into toys values('000013','Beautifull Hair Doll','Girls can change the hair style and color of this Doll .','002', 14.99,'003',NULL,55,4,8,1,null)
insert into toys values('000015','Flower Loving Doll','A doll with a bouquet of flowers in her hand.','002', 49.99,'004',NULL,43,8,9,1,null)
insert into toys values('000016','Victorian Dollhouse','A beautiful dollhouse that every girl will love.','002',43.25,'003',NULL,36,5,9,1,null)
insert into toys values('000017','Kitchen Set','A complete kitchen set with utensils, stove and all other kitchen gadgets.','006', 23.99,'002',NULL,76,5,9,2,null)
insert into toys values('000018','Childrens Bedroom','A childrens bedroom set with bunk beds with a ladder and a closet. ','006', 16.99,'005',NULL,15,5,9,2,null)
insert into toys values('000019','Nursery','A nursery with a crib and a baby.','006', 8.99,'001',NULL,35,4,9,2,null)
insert into toys values('000020','Victorian Family ','Let your child travel back in time and out for a stroll with this Victorian family. ','006', 8.99,'001',NULL,45,4,9,2,null)
insert into toys values('000021','Birthday Party','A children’s party with a magician and his tricks, a big game wheel, trees, balloons of all shapes and sizes, presents, and games. ','006', 25.99,'004',NULL,56,4,9,1,null)
insert into toys values('000023','Tin Drum','A tin drum, which is perfect for neighborhood parades. Includes carrying strap and drumsticks.','012', 15.99,'001',NULL,88,3,8,1,null)
insert into toys values('000024','Key Boom Guitar','A guitar with dual volume control and amplifying circuit and includes a shoulder strap and batteries.','012', 25.99,'001',NULL,75,5,8,1,null)
insert into toys values('000025','My First Flashlight','Makes flashlight play fun and easy. This durable flashlight has a big button for easy activation. Requires one AA battery (not included).','013', 7.99,'003',NULL,65,3,5,1,null)
insert into toys values('000026','Electronic Safe','A large size safe. Just press a button to open the safe and hear an alarm. Insert money through a secret slot in the back and use an electronic combination lock. ','013', 22.99,'005',NULL,66,5,9,1,null)
insert into toys values('000027','X-90 Racers Set','The fast-paced action racing track is the ultimate challenge for X-90 Racers. Contains cars with motors inside for incredibly fast and furious racing action. ','005', 19.99,'001',NULL,77,5,9,1,null)
insert into toys values('000028','Dune Racer','A set of dune buggies with a racing track.','005', 9.99,'004',NULL,78,4,9,1,null)
insert into toys values('000029','Spiral Zoom  Way','Give children a chance to enjoy racing excitement with this easy-to-assemble track','005', 14.99,'002',NULL,88,2,7,2,null)
insert into toys values('000030','Racing Truck','Zoom past the competition with this durable plastic truck featuring oversized tires.','005', 35.99,'005',NULL,78,3,7,2,null)
insert into toys values('000031','Large Duck','Big, bright and soft to the touch, this Large Duck. It is made of durable cotton and is filled with flameproof machine-washable material.','009', 17.99,'001',NULL,88,1,2,1,null)
insert into toys values('000032','Baby Minnie','Your infant needs to merely touch Baby Minnie, and she will shake her little rattle, just like a real Baby would. ','009', 14.99,'002',NULL,66,1,3,1,null)

/* data into shopping cart  */
insert into ShoppingCart values('000001','000001',1)
insert into ShoppingCart values('000001','000007',1)
insert into ShoppingCart values('000001','000008',1)
insert into ShoppingCart values('000002','000016',1)
insert into ShoppingCart values('000002','000009',1)
insert into ShoppingCart values('000003','000017',1)
insert into ShoppingCart values('000004','000030',1)
insert into ShoppingCart values('000004','000004',1)
insert into ShoppingCart values('000005','000001',1)
insert into ShoppingCart values('000005','000024',1)
insert into ShoppingCart values('000005','000030',1)
insert into ShoppingCart values('000005','000018',1)
insert into ShoppingCart values('000006','000017',1)
insert into ShoppingCart values('000006','000013',1)
insert into ShoppingCart values('000007','000006',1)
insert into ShoppingCart values('000008','000023',1)
insert into ShoppingCart values('000009','000018',1)

/* data for orders  */
insert into Orders values('000001','05/20/2021','000002','000002','01',6,1.2500,'Y',62.2200,'05/24/2021')
insert into Orders values('000002','05/20/2021','000001','000005','02',8,2.0000,'Y',96.5000,'05/23/2021')
insert into Orders values('000003','05/20/2021','000003','000007','01',12,0,'Y',83.9700,'05/24/2021')
insert into Orders values('000004','05/20/2021','000004','000006','01',4,1.0000,'Y',40.9900,'05/24/2021')
insert into Orders values('000005','05/21/2021','000005','000002','03',90,7.7500,'Y',231.6800,'05/25/2021')
insert into Orders values('000006','05/21/2021','000003','000012','03',40,4.0000,'Y',97.9700,'05/22/2021')
insert into Orders values('000007','05/22/2021','000002','000008','01',4,0,'Y',16.9900,'05/26/2021')
insert into Orders values('000008','05/22/2021','000002','000009','03',20,2.0000,'Y',53.9800,'05/26/2021')
insert into Orders values('000009','05/22/2021','000004','000010','02',8,2.000,'Y',26.9900,'05/25/2021')
insert into Orders values('000010','05/22/2021','000005','000003','02',20,4.0000,'Y',67.9700,'05/26/2021')

/* data for order details  */
insert into OrderDetail values('000001','000007',2,'N',NULL,NULL,39.9800)
insert into OrderDetail values('000001','000008',1,'Y','002','Surprise',14.9900)
insert into OrderDetail values('000002','000016',2,'Y','001','I Love you',86.5000)
insert into OrderDetail values('000003','000017',3,'N',NULL,NULL,71.9700)
insert into OrderDetail values('000004','000030',1,'Y','001','I Love You',35.9900)
insert into OrderDetail values('000005','000001',4,'Y','001','Happy Birthday',35.9600)
insert into OrderDetail values('000005','000024',1,'Y','002','Best Wishes',25.9900)
insert into OrderDetail values('000005','000030',2,'Y','002','Surprise',71.9800)
insert into OrderDetail values('000006','000017',1,'Y','001','With love',29.9800)
insert into OrderDetail values('000006','000013',2,'Y','003','Happy Birth day',23.9900)
insert into OrderDetail values('000007','000006',1,'N',NULL,NULL,12.9900)
insert into OrderDetail values('000008','000023',2,'Y','001','For you with love',31.9800)
insert into OrderDetail values('000009','000018',1,'Y','004','Congratulations',16.9900)
insert into OrderDetail values('000010','000020',2,'Y','005','You are the best',17.9800)
insert into OrderDetail values('000010','000021',1,'Y','001','Happy Birth day',25.9900)

/* shipment  */
insert into Shipment values('000001','05/23/2021','d','05/24/2021')
insert into Shipment values('000002','05/23/2021','d','05/23/2021')
insert into Shipment values('000003','05/23/2021','s',null)
insert into Shipment values('000004','05/24/2021','d','05/26/2021')
insert into Shipment values('000005','05/24/2021','d','05/25/2021')
insert into Shipment values('000006','05/22/2021','d','05/23/2021')
insert into Shipment values('000007','05/25/2021','s',null)
insert into Shipment values('000008','05/24/2021','d','05/24/2021')
insert into Shipment values('000009','05/24/2021','d','05/25/2021')
insert into Shipment values('000010','05/26/2021','d','05/28/2021')

/* data for recipient  */
insert into Recipient values('000001','Barbara','Johnson','227 Beach Ave.','Sunnyvale','California','001','94087-1147','123-5673')
insert into Recipient values('000002','Catherine','Roberts','5508 Aquiline Court','San Jose','California','001','95233-4123','445-2256')
insert into Recipient values('000003','Christopher','Davis','4896 11th ST','Hill Avenue','Utah','001','84056-5410','556-9087')
insert into Recipient values('000005','Barbara','Johnson','227 Beach Ave.','Sunnyvale','California','001','94087-1147','123-5673')
insert into Recipient values('000006','Donna','Anderson','7930 Orange St.','Las Vegas','Nevada','001','89328-2517','845-2323')
insert into Recipient values('000009','David','Moore','8808 Joviality Drive','San Ramon','California','001','94453-5849','982-5577')
insert into Recipient values('000010','Betty','Williams','1 Tread Road','Virginia Beach','Virginia','001','23455-2456','458-3299')
insert into Recipient values('000004','Jennifer','Martin','9812  76th Street','Brooklyn','Maryland','001','21254-0025','569-7789')
insert into Recipient values('000007','Laura','Rodriguez','3242 Limestone  ','WayMarietta','Georgia','001','30062-5423','567-3345')
insert into Recipient values('000008','Michelle','Hernandez','1353 Realm Lakes','Naperville','Illinois','001','60563-1256','294-5385')

/* inserting date in pickofmonth table*/
insert into pickofmonth
values('000001',1,2020,1000)
insert into pickofmonth
values('000001',2,2020,1230)
insert into pickofmonth
values('000005',3,2020,4000)
insert into pickofmonth
values('000007',4,2020,5000)
insert into pickofmonth
values('000003',5,2020,2020)
insert into pickofmonth
values('000002',6,2020,3000)
insert into pickofmonth
values('000003',7,2020,5670)
insert into pickofmonth
values('000007',8,2020,2340)
insert into pickofmonth
values('000011',9,2020,5600)
insert into pickofmonth
values('000020',10,2020,2300)
insert into pickofmonth
values('000021',11,2020,4500)
insert into pickofmonth
values('000026',12,2020,6500)
insert into pickofmonth
values('000024',1,2021,3200)
insert into pickofmonth
values('000015',2,2021,3100)
insert into pickofmonth
values('000012',3,2021,2500)

go

raiserror('The GlobalToyz database in now ready for use....',0,1)
