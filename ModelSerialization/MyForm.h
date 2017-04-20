#pragma once
#include <iostream>

namespace ModelSerialization {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	using namespace IO;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  textBox1;
	protected:

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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(277, 400);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(103, 63);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Load and draw";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(200, 61);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(398, 324);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(449, 400);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 63);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Rotate";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(553, 418);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(113, 26);
			this->textBox1->TabIndex = 3;
			this->textBox1->Text = Convert::ToString(15);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(778, 544);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(800, 600);
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(800, 600);
			this->Name = L"MyForm";
			this->Text = L"Model";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		List<PointF> ^points;
		
		System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			start();
		}
		
		void start() {
			 StreamReader^ stream = File::OpenText("./Square.txt");
			 String^ s = stream->ReadLine();
			 if (!s) {
				 return;
			 }
			 points = gcnew List<PointF>();
			 int i = 0;
			 for each(String^ string in s->Split(' ')) {
				 points->Add(PointF(Convert::ToDouble(string->Substring(0, 3)), Convert::ToDouble(string->Substring(4))));
				 i++;
			 }
			 reDraw();
		}

		void reDraw() {
			 pictureBox1->Refresh();
			 Color color = Color::BlueViolet;
			 Pen^ pen = gcnew Pen(color);
			 Graphics^ g = this->pictureBox1->CreateGraphics();
			 for (int i = 0; i < points->Count; i += 2) {
				 g->DrawLine(pen, points[i], points[i + 1]);
			 }
		}
		System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			rotate(Convert::ToInt16(this->textBox1->Text));
		}

		void rotate(int degree) {
			double radians = (double) degree / (double) 57.3;
			List<double>^ matrix = gcnew List<double>();
			List<PointF>^ points1 = gcnew List<PointF>();
			matrix->Add(Math::Cos(radians));
			matrix->Add(-Math::Sin(radians));
			matrix->Add(Math::Sin(radians));
			matrix->Add(Math::Cos(radians));
			int d = 100;
			for each(PointF point in points) {
				double x = (double)point.X - d;
				double y = (double)point.Y - d;
				points1->Add(PointF(matrix[0] * x + matrix[1] * y + d, matrix[2] * x + matrix[3] * y + d));
			}
			points = points1;
			reDraw();
		}
};
}
