#pragma once

namespace PBC {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;



	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:


	private: System::Windows::Forms::TextBox^  srcFile_txt;
	private: System::Windows::Forms::Label^    srcFile_lbl;
	private: System::Windows::Forms::Button^   srcFile_btn;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  archFile_txt;

	private: System::Windows::Forms::Button^  archFile_btn;
	private: System::Windows::Forms::Button^  compress_btn;
	private: System::Windows::Forms::Button^  decompress_btn;
	private: System::Windows::Forms::Button^  details_btn;
	private: System::Windows::Forms::Button^  test_btn;
	private: System::Windows::Forms::RichTextBox^  msg_txt;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->srcFile_txt = (gcnew System::Windows::Forms::TextBox());
			this->srcFile_lbl = (gcnew System::Windows::Forms::Label());
			this->srcFile_btn = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->archFile_txt = (gcnew System::Windows::Forms::TextBox());
			this->archFile_btn = (gcnew System::Windows::Forms::Button());
			this->compress_btn = (gcnew System::Windows::Forms::Button());
			this->decompress_btn = (gcnew System::Windows::Forms::Button());
			this->details_btn = (gcnew System::Windows::Forms::Button());
			this->test_btn = (gcnew System::Windows::Forms::Button());
			this->msg_txt = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// srcFile_txt
			// 
			this->srcFile_txt->BackColor = System::Drawing::Color::AliceBlue;
			this->srcFile_txt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->srcFile_txt->ForeColor = System::Drawing::SystemColors::WindowText;
			this->srcFile_txt->Location = System::Drawing::Point(110, 13);
			this->srcFile_txt->Name = L"srcFile_txt";
			this->srcFile_txt->Size = System::Drawing::Size(470, 23);
			this->srcFile_txt->TabIndex = 1;
			this->srcFile_txt->TextChanged += gcnew System::EventHandler(this, &MainForm::srcFile_txt_TextChanged);
			// 
			// srcFile_lbl
			// 
			this->srcFile_lbl->AutoSize = true;
			this->srcFile_lbl->Font = (gcnew System::Drawing::Font(L"Georgia", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->srcFile_lbl->ForeColor = System::Drawing::SystemColors::GrayText;
			this->srcFile_lbl->Location = System::Drawing::Point(18, 15);
			this->srcFile_lbl->Name = L"srcFile_lbl";
			this->srcFile_lbl->Size = System::Drawing::Size(82, 17);
			this->srcFile_lbl->TabIndex = 2;
			this->srcFile_lbl->Text = L"Source file :";
			// 
			// srcFile_btn
			// 
			this->srcFile_btn->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->srcFile_btn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->srcFile_btn->Font = (gcnew System::Drawing::Font(L"Georgia", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->srcFile_btn->Location = System::Drawing::Point(598, 13);
			this->srcFile_btn->Name = L"srcFile_btn";
			this->srcFile_btn->Size = System::Drawing::Size(70, 23);
			this->srcFile_btn->TabIndex = 3;
			this->srcFile_btn->Text = L"Open";
			this->srcFile_btn->UseVisualStyleBackColor = false;
			this->srcFile_btn->Click += gcnew System::EventHandler(this, &MainForm::srcFile_btn_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Georgia", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::SystemColors::GrayText;
			this->label1->Location = System::Drawing::Point(12, 46);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(88, 17);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Archive file :";
			// 
			// archFile_txt
			// 
			this->archFile_txt->BackColor = System::Drawing::Color::MintCream;
			this->archFile_txt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->archFile_txt->ForeColor = System::Drawing::SystemColors::WindowText;
			this->archFile_txt->Location = System::Drawing::Point(110, 43);
			this->archFile_txt->Name = L"archFile_txt";
			this->archFile_txt->Size = System::Drawing::Size(470, 23);
			this->archFile_txt->TabIndex = 5;
			this->archFile_txt->TextChanged += gcnew System::EventHandler(this, &MainForm::archFile_txt_TextChanged);
			// 
			// archFile_btn
			// 
			this->archFile_btn->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->archFile_btn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->archFile_btn->Font = (gcnew System::Drawing::Font(L"Georgia", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->archFile_btn->Location = System::Drawing::Point(598, 43);
			this->archFile_btn->Name = L"archFile_btn";
			this->archFile_btn->Size = System::Drawing::Size(70, 23);
			this->archFile_btn->TabIndex = 6;
			this->archFile_btn->Text = L"Open";
			this->archFile_btn->UseVisualStyleBackColor = false;
			this->archFile_btn->Click += gcnew System::EventHandler(this, &MainForm::archFile_btn_Click);
			// 
			// compress_btn
			// 
			this->compress_btn->BackColor = System::Drawing::Color::AliceBlue;
			this->compress_btn->Enabled = false;
			this->compress_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::SteelBlue;
			this->compress_btn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->compress_btn->Font = (gcnew System::Drawing::Font(L"Georgia", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->compress_btn->ForeColor = System::Drawing::Color::SteelBlue;
			this->compress_btn->Location = System::Drawing::Point(110, 72);
			this->compress_btn->Name = L"compress_btn";
			this->compress_btn->Size = System::Drawing::Size(110, 40);
			this->compress_btn->TabIndex = 7;
			this->compress_btn->Text = L"COMPRESS";
			this->compress_btn->UseVisualStyleBackColor = false;
			this->compress_btn->Click += gcnew System::EventHandler(this, &MainForm::compress_btn_Click);
			// 
			// decompress_btn
			// 
			this->decompress_btn->BackColor = System::Drawing::Color::MintCream;
			this->decompress_btn->Enabled = false;
			this->decompress_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::SeaGreen;
			this->decompress_btn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->decompress_btn->Font = (gcnew System::Drawing::Font(L"Georgia", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->decompress_btn->ForeColor = System::Drawing::Color::SeaGreen;
			this->decompress_btn->Location = System::Drawing::Point(230, 72);
			this->decompress_btn->Name = L"decompress_btn";
			this->decompress_btn->Size = System::Drawing::Size(110, 40);
			this->decompress_btn->TabIndex = 8;
			this->decompress_btn->Text = L"DECOMPRESS";
			this->decompress_btn->UseVisualStyleBackColor = false;
			this->decompress_btn->Click += gcnew System::EventHandler(this, &MainForm::decompress_btn_Click);
			// 
			// details_btn
			// 
			this->details_btn->BackColor = System::Drawing::Color::Beige;
			this->details_btn->Enabled = false;
			this->details_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Olive;
			this->details_btn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->details_btn->Font = (gcnew System::Drawing::Font(L"Georgia", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->details_btn->ForeColor = System::Drawing::Color::Olive;
			this->details_btn->Location = System::Drawing::Point(350, 72);
			this->details_btn->Name = L"details_btn";
			this->details_btn->Size = System::Drawing::Size(110, 40);
			this->details_btn->TabIndex = 9;
			this->details_btn->Text = L"DETAILS";
			this->details_btn->UseVisualStyleBackColor = false;
			this->details_btn->Click += gcnew System::EventHandler(this, &MainForm::details_btn_Click);
			// 
			// test_btn
			// 
			this->test_btn->BackColor = System::Drawing::Color::SeaShell;
			this->test_btn->Enabled = false;
			this->test_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Sienna;
			this->test_btn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->test_btn->Font = (gcnew System::Drawing::Font(L"Georgia", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->test_btn->ForeColor = System::Drawing::Color::Sienna;
			this->test_btn->Location = System::Drawing::Point(470, 72);
			this->test_btn->Name = L"test_btn";
			this->test_btn->Size = System::Drawing::Size(110, 40);
			this->test_btn->TabIndex = 10;
			this->test_btn->Text = L"TEST";
			this->test_btn->UseVisualStyleBackColor = false;
			this->test_btn->Click += gcnew System::EventHandler(this, &MainForm::test_btn_Click);
			// 
			// msg_txt
			// 
			this->msg_txt->BackColor = System::Drawing::Color::Beige;
			this->msg_txt->Location = System::Drawing::Point(110, 119);
			this->msg_txt->Name = L"msg_txt";
			this->msg_txt->ReadOnly = true;
			this->msg_txt->Size = System::Drawing::Size(470, 255);
			this->msg_txt->TabIndex = 11;
			this->msg_txt->Text = L"";
			// 
			// MainForm
			// 
			this->AccessibleRole = System::Windows::Forms::AccessibleRole::Application;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Menu;
			this->ClientSize = System::Drawing::Size(684, 386);
			this->Controls->Add(this->msg_txt);
			this->Controls->Add(this->test_btn);
			this->Controls->Add(this->details_btn);
			this->Controls->Add(this->decompress_btn);
			this->Controls->Add(this->compress_btn);
			this->Controls->Add(this->archFile_btn);
			this->Controls->Add(this->archFile_txt);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->srcFile_btn);
			this->Controls->Add(this->srcFile_lbl);
			this->Controls->Add(this->srcFile_txt);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->HelpButton = true;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MainForm";
			this->Text = L"PBC";
			this->TransparencyKey = System::Drawing::Color::Gray;
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
private: System::Void srcFile_btn_Click(System::Object^  sender, System::EventArgs^  e) {
	// OPEN FILE FOR COMPRESSION
	OpenFileDialog^ openfilec = gcnew OpenFileDialog;
	openfilec->ShowDialog();
	srcFile_txt->Text = openfilec->FileName;					// Put srcFile path into txtField

}

private: System::Void archFile_btn_Click(System::Object^  sender, System::EventArgs^  e) {
	// OPEN FILE FOR DECOMPRESSION
	OpenFileDialog^ openfiled = gcnew OpenFileDialog;
	openfiled->Filter = "Zip Files|*.zip;*.rar";				// Apply filter - only archive files
	openfiled->ShowDialog();
	archFile_txt->Text = openfiled->FileName;					// Put archFile path into txtField
}
		 /*
			WHEN SRC FIELD AND ARCH FIELD GET PATHS -> ENABLE COMPRESS BUTTON
		 */
private: System::Void srcFile_txt_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	if (srcFile_txt->Text != "" && archFile_txt->Text != "") {
		compress_btn->Enabled = true;
	}
	else {
		compress_btn->Enabled = false;
	}
}
		 /*
			WHEN ARCH FIELD GET A PATH -> ENABLE DECOMPRESS, DETAILS, TEST BUTTONS
			IF SRC PATH HAVE A PATH TO -> ENABLE COMPRESS BUTTON TOO
		 */
private: System::Void archFile_txt_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	if (archFile_txt->Text != "") {
		decompress_btn->Enabled = true;
		details_btn->Enabled = true;
		test_btn->Enabled = true;
		if (srcFile_txt->Text != "") {
			compress_btn->Enabled = true;
		}
		else {
			compress_btn->Enabled = false;
		}
	}
	else {
		decompress_btn->Enabled = false;
		details_btn->Enabled = false;
		test_btn->Enabled = false;
		compress_btn->Enabled = false;
	}
}

		 /* 
			COMPRESS BUTTON CLICK
		 *	read file in byte format
		 *	check for correct predictors
		 *	put the best predictor and the stream length in PREDICTORS FILE
		 *	put the residue and the initial data (having first length) in the RESIDUE FILE
		 *	don't forget about the DETAILS FILE ( name, time, length, compression factor, checksums)
		 */
private: System::Void compress_btn_Click(System::Object^  sender, System::EventArgs^  e) {
	


}

		 /* 
			DECOMPRESS BUTTON CLICK
		 *	read data from files (residue and predictors)
		 *	restore the original file by checking used predictors and adding residue at the initial data
		 */
private: System::Void decompress_btn_Click(System::Object^  sender, System::EventArgs^  e) {

}

		 /* 
			DETAILS BUTTON CLICK
		 *	read data from details file
		 */
private: System::Void details_btn_Click(System::Object^  sender, System::EventArgs^  e) {

}

		 /* 
			TEST BUTTON CLICK
		 *	compare checksums (after compression and calculated for decompressed file when this btn is clicked)
		 */
private: System::Void test_btn_Click(System::Object^  sender, System::EventArgs^  e) {

}
};
}
