#pragma once
#include "MainForm.h"
using namespace System::Data;
using namespace System::Data::SqlClient;

namespace AlcoholProductionApp {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class MainForm : public Form
    {
    public:
        MainForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~MainForm()
        {
            if (components)
                delete components;
        }

    private:
        DataGridView^ dataGridView1;
        Button^ btnAdd;
        Button^ btnRemove;
        Button^ btnEdit;
        Button^ btnSearch;
        Button^ btnLoad;

        TextBox^ txtType;
        TextBox^ txtBrand;
        TextBox^ txtManufacturer;
        TextBox^ txtSupplier;
        TextBox^ txtExpirationDate;
        TextBox^ txtPrice;

        TextBox^ textBoxSearch;
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->dataGridView1 = gcnew DataGridView();
            this->btnAdd = gcnew Button();
            this->btnRemove = gcnew Button();
            this->btnEdit = gcnew Button();
            this->btnLoad = gcnew Button();
            this->btnSearch = gcnew Button();
            this->textBoxSearch = gcnew TextBox();

            this->txtType = gcnew TextBox();
            this->txtBrand = gcnew TextBox();
            this->txtManufacturer = gcnew TextBox();
            this->txtSupplier = gcnew TextBox();
            this->txtExpirationDate = gcnew TextBox();
            this->txtPrice = gcnew TextBox();

            this->SuspendLayout();

            this->dataGridView1->Location = Point(12, 12);
            this->dataGridView1->Size = Drawing::Size(600, 200);
            this->dataGridView1->SelectionMode = DataGridViewSelectionMode::FullRowSelect;

            this->btnAdd->Text = L"Add"; this->btnAdd->Location = Point(630, 12);
            this->btnRemove->Text = L"Remove"; this->btnRemove->Location = Point(630, 50);
            this->btnEdit->Text = L"Edit"; this->btnEdit->Location = Point(630, 88);
            this->btnLoad->Text = L"Load Drinks"; this->btnLoad->Location = Point(630, 140);
            this->btnSearch->Text = L"Search"; this->btnSearch->Location = Point(130, 219);

            this->txtType->Location = Point(630, 210);
            this->txtBrand->Location = Point(630, 240);
            this->txtManufacturer->Location = Point(630, 270);
            this->txtSupplier->Location = Point(630, 300);
            this->txtExpirationDate->Location = Point(630, 330);
            this->txtPrice->Location = Point(630, 360);

            this->textBoxSearch->Location = Point (20, 220);


            this->Controls->Add(this->dataGridView1);
            this->Controls->Add(this->btnAdd);
            this->Controls->Add(this->btnRemove);
            this->Controls->Add(this->btnEdit);
            this->Controls->Add(this->btnLoad);
            this->Controls->Add(this->btnSearch);
            this->Controls->Add(this->textBoxSearch);

            this->Controls->Add(this->txtType);
            this->Controls->Add(this->txtBrand);
            this->Controls->Add(this->txtManufacturer);
            this->Controls->Add(this->txtSupplier);
            this->Controls->Add(this->txtExpirationDate);
            this->Controls->Add(this->txtPrice);

            this->ClientSize = Drawing::Size(800, 450);
            this->Text = L"Alcohol Production App";
            this->Load += gcnew EventHandler(this, &MainForm::MainForm_Load);

            this->btnLoad->Click += gcnew EventHandler(this, &MainForm::btnLoad_Click);
            this->btnAdd->Click += gcnew EventHandler(this, &MainForm::btnAdd_Click);
            this->btnRemove->Click += gcnew EventHandler(this, &MainForm::btnRemove_Click);
            this->btnEdit->Click += gcnew EventHandler(this, &MainForm::btnEdit_Click);
            this->btnSearch->Click += gcnew EventHandler(this, &MainForm::btnSearch_Click);


            this->ResumeLayout(false);
        }
#pragma endregion

    private:
        void MainForm_Load(System::Object^ sender, System::EventArgs^ e)
        {
            // нічого не створюємо вручну, колонки підхопляться з SQL
            btnLoad_Click(sender, e); // одразу завантажуємо дані
        }


        void btnLoad_Click(System::Object^ sender, System::EventArgs^ e)
        {
            try
            {
                String^ connStr = "Server=localhost\\SQLEXPRESS;Database=AlcoholProductionDB;Integrated Security=True;";
                SqlConnection^ conn = gcnew SqlConnection(connStr);
                conn->Open();

                String^ query = "SELECT Type, Brand, Manufacturer, Supplier, ExpirationDate, Price FROM Drinks";
                SqlDataAdapter^ adapter = gcnew SqlDataAdapter(query, conn);
                DataTable^ dt = gcnew DataTable();
                adapter->Fill(dt);

                dataGridView1->DataSource = dt;

                conn->Close();
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Error: " + ex->Message);
            }
        }

        // Додати новий рядок у DataTable, до якого прив'язаний DataGridView
        void btnAdd_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (txtType->Text == "" || txtBrand->Text == "")
            {
                MessageBox::Show("Type and Brand are required");
                return;
            }

            try
            {
                String^ connStr = "Server=localhost\\SQLEXPRESS;Database=AlcoholProductionDB;Integrated Security=True;";
                SqlConnection^ conn = gcnew SqlConnection(connStr);
                conn->Open();

                String^ query = "INSERT INTO Drinks (Type, Brand, Manufacturer, Supplier, ExpirationDate, Price) " +
                    "VALUES (@Type, @Brand, @Manufacturer, @Supplier, @ExpirationDate, @Price)";

                SqlCommand^ cmd = gcnew SqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@Type", txtType->Text);
                cmd->Parameters->AddWithValue("@Brand", txtBrand->Text);
                cmd->Parameters->AddWithValue("@Manufacturer", txtManufacturer->Text);
                cmd->Parameters->AddWithValue("@Supplier", txtSupplier->Text);
                cmd->Parameters->AddWithValue("@ExpirationDate", txtExpirationDate->Text);
                cmd->Parameters->AddWithValue("@Price", txtPrice->Text);

                cmd->ExecuteNonQuery();
                conn->Close();

                // Оновлюємо DataGridView після INSERT
                btnLoad_Click(sender, e);

                // Очистка полів
                txtType->Clear(); txtBrand->Clear(); txtManufacturer->Clear();
                txtSupplier->Clear(); txtExpirationDate->Clear(); txtPrice->Clear();
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Error: " + ex->Message);
            }
        }


        void btnRemove_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (dataGridView1->SelectedRows->Count == 0) return;

            try
            {
                String^ connStr = "Server=localhost\\SQLEXPRESS;Database=AlcoholProductionDB;Integrated Security=True;";
                SqlConnection^ conn = gcnew SqlConnection(connStr);
                conn->Open();

                for each (DataGridViewRow ^ row in dataGridView1->SelectedRows)
                {
                    String^ type = row->Cells["Type"]->Value->ToString();
                    String^ brand = row->Cells["Brand"]->Value->ToString();

                    String^ query = "DELETE FROM Drinks WHERE Type=@Type AND Brand=@Brand";
                    SqlCommand^ cmd = gcnew SqlCommand(query, conn);
                    cmd->Parameters->AddWithValue("@Type", type);
                    cmd->Parameters->AddWithValue("@Brand", brand);
                    cmd->ExecuteNonQuery();

                    break; // тільки перший рядок видаляємо
                }

                conn->Close();

                // Оновлюємо DataGridView
                btnLoad_Click(sender, e);
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Error: " + ex->Message);
            }
        }


        void btnEdit_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (dataGridView1->SelectedRows->Count == 0) return;

            try
            {
                String^ connStr = "Server=localhost\\SQLEXPRESS;Database=AlcoholProductionDB;Integrated Security=True;";
                SqlConnection^ conn = gcnew SqlConnection(connStr);
                conn->Open();

                DataGridViewRow^ row = dataGridView1->SelectedRows[0];

                String^ oldType = row->Cells["Type"]->Value->ToString();
                String^ oldBrand = row->Cells["Brand"]->Value->ToString();

                String^ query = "UPDATE Drinks SET Type=@Type, Brand=@Brand, Manufacturer=@Manufacturer, Supplier=@Supplier, ExpirationDate=@ExpirationDate, Price=@Price " +
                    "WHERE Type=@OldType AND Brand=@OldBrand";

                SqlCommand^ cmd = gcnew SqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@Type", txtType->Text);
                cmd->Parameters->AddWithValue("@Brand", txtBrand->Text);
                cmd->Parameters->AddWithValue("@Manufacturer", txtManufacturer->Text);
                cmd->Parameters->AddWithValue("@Supplier", txtSupplier->Text);
                cmd->Parameters->AddWithValue("@ExpirationDate", txtExpirationDate->Text);
                cmd->Parameters->AddWithValue("@Price", txtPrice->Text);
                cmd->Parameters->AddWithValue("@OldType", oldType);
                cmd->Parameters->AddWithValue("@OldBrand", oldBrand);

                cmd->ExecuteNonQuery();
                conn->Close();

                // Оновлюємо DataGridView
                btnLoad_Click(sender, e);

                // Очистка полів
                txtType->Clear(); txtBrand->Clear(); txtManufacturer->Clear();
                txtSupplier->Clear(); txtExpirationDate->Clear(); txtPrice->Clear();
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Error: " + ex->Message);
            }

        }
        void btnSearch_Click(System::Object^ sender, System::EventArgs^ e)
        {
            String^ searchTerm = this->textBoxSearch->Text->Trim();

            DataTable^ dt = dynamic_cast<DataTable^>(this->dataGridView1->DataSource);
            if (dt == nullptr) return;

            if (searchTerm == "")
            {
                dt->DefaultView->RowFilter = "";
            }
            else
            {
                // Перелік колонок для пошуку (ігноруємо ExpirationDate)
                array<String^>^ columns = { "Type", "Brand", "Manufacturer", "Supplier" };
                String^ filter = "";

                for each (String ^ col in columns)
                {
                    if (filter != "") filter += " OR ";
                    filter += String::Format("{0} LIKE '%{1}%'", col, searchTerm);
                }

                dt->DefaultView->RowFilter = filter;
            }
        }



    };
}
