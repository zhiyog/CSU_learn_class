	 /*      Install GlobalToyz database             */
set nocount    on
USE master

declare @dttm varchar(55)
select  @dttm=convert(varchar,getdate(),113)
raiserror('Starting installation of GlobalToyz Database at %s ....',1,1,@dttm) with nowait
GO

if exists (select * from sysdatabases where name='GlobalToyz')
begin
  raiserror('Dropping existing GlobalToyz database ....',0,1)
  DROP database GlobalToyz
end
GO

CHECKPOINT
go

raiserror('Creating GlobalToyz database....',0,1)
go
   CREATE DATABASE GlobalToyz
GO

CHECKPOINT
GO

USE GlobalToyz
GO

if db_name() <> 'GlobalToyz'
   raiserror('Error in installToy.SQL, ''USE GlobalToyz'' failed!  Killing the SPID now.'
            ,22,127) with log
GO

execute sp_dboption 'GlobalToyz','trunc. log on chkpt.' ,'true'

execute sp_dboption 'GlobalToyz','SELECT INTO/BULKCOPY', 'true'
checkpoint
