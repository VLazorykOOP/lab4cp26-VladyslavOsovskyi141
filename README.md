Цей проект використовує **Microsoft SQL Server**.
Будь-ласка, створіть датабазу "AlcoholProductionDB"

Та створіть таблиці до неї, через:
USE AlcoholProductionDB;

CREATE TABLE Drinks (
    Type NVARCHAR(100) NOT NULL,
    Brand NVARCHAR(100) NOT NULL,
    Manufacturer NVARCHAR(100),
    Supplier NVARCHAR(100),
    ExpirationDate NVARCHAR(50),
    Price DECIMAL(10, 2)
);

Інформація про датабазу
Server=localhost\SQLEXPRESS;
Database=AlcoholProductionDB;
Integrated Security=True;

Якщо ім'я вашого instance з серверу інше, змініть його у MainForm.h

Щоби запустити програму:
Клонуйте репо, запустіть AlcoholProductionApp.sln в VS (було зроблено у 2022), Build the solution та можете запускати .exe Build

Пояснення як працювати з програмою, кнопки:
Є 6 колонок в які ви можете вводити дані: Тип, Бренд, Виробник, Постачальник, Дату строку дії та ціну.
Add додає колонку (та що позначена зірочкою), Edit замінює ті дані на виділеній колонці
Remove видаляє виділену колонку
Load Drinks перезавантажує все те що є в датабазі,
Search допомогає знайти той бренд чи ім'я товару (працює тільки з текстом!)

## Дякую за увагу!









