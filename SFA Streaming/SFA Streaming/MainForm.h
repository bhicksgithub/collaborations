#pragma once

#include "CameraPreview.h"
#include "cPhotonMAX.h"
#include "cPixeLINK.h"
#include "CameraParameters.h"
#include "fitsio.h"
#include <fstream>

namespace VNCTest {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::Drawing::Imaging;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		cPhotonMAX *pmCam = NULL;
	private: System::Windows::Forms::GroupBox^  pmFrameGroupBox;
	public:
	private: System::Windows::Forms::NumericUpDown^  pmFrameControl;

	public:
		cPixeLINK *plCam = NULL;

		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		System::Void PreviewThread(Object ^data) {
			CameraParameters ^params = dynamic_cast<CameraParameters ^>(data);
			CameraPreview ^preview = params->prev;
			Camera *cam = params->cam;

			while (preview->Visible) {
				array<unsigned char> ^pdata = cam->getFrame();

				System::Drawing::Imaging::PixelFormat pxlFmt;
				pxlFmt = System::Drawing::Imaging::PixelFormat::Format24bppRgb;
				Bitmap ^bmp = gcnew Bitmap(cam->WX, cam->WY, pxlFmt);
				System::Drawing::Rectangle rect = 
					System::Drawing::Rectangle(0, 0, bmp->Width, bmp->Height);
				BitmapData ^bmpData;
				
				try
				{
					bmpData = bmp->LockBits(rect, ImageLockMode::WriteOnly, 
						pxlFmt);
					System::Runtime::InteropServices::Marshal::Copy(pdata, 0, 
						bmpData->Scan0, pdata->Length);// cam->WX * cam->WY * 3);
				}
				finally
				{
					bmp->UnlockBits(bmpData);
				}

				//bmp->RotateFlip(RotateFlipType::Rotate180FlipX);
				preview->updatePreview(bmp);
				delete pdata;
			}

			delete params;
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
	private: System::Windows::Forms::GroupBox^  groupBoxPL;
	private: System::Windows::Forms::GroupBox^  groupBoxPM;
	private: System::Windows::Forms::TextBox^  pmExpTextBox;
	protected:

	protected:




	private: System::Windows::Forms::SaveFileDialog^  pmSaveDialog;



	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TrackBar^  pmExpTrackBar;
	private: System::Windows::Forms::GroupBox^  pmGroupBox2;


	private: System::Windows::Forms::Button^  pmSaveButton;
	private: System::Windows::Forms::Button^  pmPreview;
	private: System::Windows::Forms::NumericUpDown^  pmGainControl;
	private: System::Windows::Forms::GroupBox^  pmROIGroupBox;
	private: System::Windows::Forms::NumericUpDown^  pmROIYEndC;
	private: System::Windows::Forms::Label^  pmROIYEnd;
	private: System::Windows::Forms::Label^  pmROIYStart;
	private: System::Windows::Forms::NumericUpDown^  pmROIYStartC;
	private: System::Windows::Forms::NumericUpDown^  pmROIXEndC;
	private: System::Windows::Forms::Label^  pmROIXEnd;
	private: System::Windows::Forms::Label^  pmROIXStart;
	private: System::Windows::Forms::NumericUpDown^  pmROIXStartC;
	private: System::Windows::Forms::Button^  plPreviewButton;
	private: System::Windows::Forms::Button^  plSaveButton;
	private: System::Windows::Forms::GroupBox^  plGainGroupBox;
	private: System::Windows::Forms::NumericUpDown^  plGainControl;
	private: System::Windows::Forms::GroupBox^  plExpGroupBox;
	private: System::Windows::Forms::TrackBar^  plExpTrackBar;
	private: System::Windows::Forms::TextBox^  plExpTextBox;




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
			this->groupBoxPL = (gcnew System::Windows::Forms::GroupBox());
			this->plPreviewButton = (gcnew System::Windows::Forms::Button());
			this->plSaveButton = (gcnew System::Windows::Forms::Button());
			this->plGainGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->plGainControl = (gcnew System::Windows::Forms::NumericUpDown());
			this->plExpGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->plExpTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->plExpTextBox = (gcnew System::Windows::Forms::TextBox());
			this->groupBoxPM = (gcnew System::Windows::Forms::GroupBox());
			this->pmROIGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->pmROIYEndC = (gcnew System::Windows::Forms::NumericUpDown());
			this->pmROIYEnd = (gcnew System::Windows::Forms::Label());
			this->pmROIYStart = (gcnew System::Windows::Forms::Label());
			this->pmROIYStartC = (gcnew System::Windows::Forms::NumericUpDown());
			this->pmROIXEndC = (gcnew System::Windows::Forms::NumericUpDown());
			this->pmROIXEnd = (gcnew System::Windows::Forms::Label());
			this->pmROIXStart = (gcnew System::Windows::Forms::Label());
			this->pmROIXStartC = (gcnew System::Windows::Forms::NumericUpDown());
			this->pmSaveButton = (gcnew System::Windows::Forms::Button());
			this->pmGroupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->pmGainControl = (gcnew System::Windows::Forms::NumericUpDown());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->pmExpTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->pmExpTextBox = (gcnew System::Windows::Forms::TextBox());
			this->pmPreview = (gcnew System::Windows::Forms::Button());
			this->pmSaveDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->pmFrameGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->pmFrameControl = (gcnew System::Windows::Forms::NumericUpDown());
			this->groupBoxPL->SuspendLayout();
			this->plGainGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->plGainControl))->BeginInit();
			this->plExpGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->plExpTrackBar))->BeginInit();
			this->groupBoxPM->SuspendLayout();
			this->pmROIGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pmROIYEndC))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pmROIYStartC))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pmROIXEndC))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pmROIXStartC))->BeginInit();
			this->pmGroupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pmGainControl))->BeginInit();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pmExpTrackBar))->BeginInit();
			this->pmFrameGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pmFrameControl))->BeginInit();
			this->SuspendLayout();
			// 
			// groupBoxPL
			// 
			this->groupBoxPL->Controls->Add(this->plPreviewButton);
			this->groupBoxPL->Controls->Add(this->plSaveButton);
			this->groupBoxPL->Controls->Add(this->plGainGroupBox);
			this->groupBoxPL->Controls->Add(this->plExpGroupBox);
			this->groupBoxPL->Location = System::Drawing::Point(12, 12);
			this->groupBoxPL->Name = L"groupBoxPL";
			this->groupBoxPL->Size = System::Drawing::Size(532, 140);
			this->groupBoxPL->TabIndex = 0;
			this->groupBoxPL->TabStop = false;
			this->groupBoxPL->Text = L"Pupil (PixeLINK Camera)";
			// 
			// plPreviewButton
			// 
			this->plPreviewButton->Location = System::Drawing::Point(437, 19);
			this->plPreviewButton->Name = L"plPreviewButton";
			this->plPreviewButton->Size = System::Drawing::Size(77, 110);
			this->plPreviewButton->TabIndex = 7;
			this->plPreviewButton->Text = L"Preview";
			this->plPreviewButton->UseVisualStyleBackColor = true;
			this->plPreviewButton->Click += gcnew System::EventHandler(this, &MainForm::plPreviewButton_Click);
			// 
			// plSaveButton
			// 
			this->plSaveButton->Location = System::Drawing::Point(354, 19);
			this->plSaveButton->Name = L"plSaveButton";
			this->plSaveButton->Size = System::Drawing::Size(77, 110);
			this->plSaveButton->TabIndex = 6;
			this->plSaveButton->Text = L"Save";
			this->plSaveButton->UseVisualStyleBackColor = true;
			this->plSaveButton->Click += gcnew System::EventHandler(this, &MainForm::plSaveButton_Click);
			// 
			// plGainGroupBox
			// 
			this->plGainGroupBox->Controls->Add(this->plGainControl);
			this->plGainGroupBox->Location = System::Drawing::Point(156, 19);
			this->plGainGroupBox->Name = L"plGainGroupBox";
			this->plGainGroupBox->Size = System::Drawing::Size(192, 110);
			this->plGainGroupBox->TabIndex = 4;
			this->plGainGroupBox->TabStop = false;
			this->plGainGroupBox->Text = L"Gain";
			// 
			// plGainControl
			// 
			this->plGainControl->DecimalPlaces = 2;
			this->plGainControl->Location = System::Drawing::Point(6, 22);
			this->plGainControl->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1397, 0, 0, 131072 });
			this->plGainControl->Name = L"plGainControl";
			this->plGainControl->Size = System::Drawing::Size(88, 20);
			this->plGainControl->TabIndex = 5;
			this->plGainControl->ValueChanged += gcnew System::EventHandler(this, &MainForm::plGainControl_ValueChanged);
			// 
			// plExpGroupBox
			// 
			this->plExpGroupBox->Controls->Add(this->plExpTrackBar);
			this->plExpGroupBox->Controls->Add(this->plExpTextBox);
			this->plExpGroupBox->Location = System::Drawing::Point(19, 19);
			this->plExpGroupBox->Name = L"plExpGroupBox";
			this->plExpGroupBox->Size = System::Drawing::Size(131, 110);
			this->plExpGroupBox->TabIndex = 1;
			this->plExpGroupBox->TabStop = false;
			this->plExpGroupBox->Text = L"Exposure time (μsec)";
			// 
			// plExpTrackBar
			// 
			this->plExpTrackBar->LargeChange = 100;
			this->plExpTrackBar->Location = System::Drawing::Point(7, 51);
			this->plExpTrackBar->Maximum = 2000000;
			this->plExpTrackBar->Minimum = 100;
			this->plExpTrackBar->Name = L"plExpTrackBar";
			this->plExpTrackBar->Size = System::Drawing::Size(118, 45);
			this->plExpTrackBar->TabIndex = 3;
			this->plExpTrackBar->TickFrequency = 100000;
			this->plExpTrackBar->Value = 100;
			this->plExpTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::plExpTrackBar_ValueChanged);
			// 
			// plExpTextBox
			// 
			this->plExpTextBox->Location = System::Drawing::Point(6, 22);
			this->plExpTextBox->Name = L"plExpTextBox";
			this->plExpTextBox->Size = System::Drawing::Size(119, 20);
			this->plExpTextBox->TabIndex = 2;
			this->plExpTextBox->Text = L"100";
			this->plExpTextBox->TextChanged += gcnew System::EventHandler(this, &MainForm::plExpTextBox_TextChanged);
			// 
			// groupBoxPM
			// 
			this->groupBoxPM->Controls->Add(this->pmFrameGroupBox);
			this->groupBoxPM->Controls->Add(this->pmROIGroupBox);
			this->groupBoxPM->Controls->Add(this->pmSaveButton);
			this->groupBoxPM->Controls->Add(this->pmGroupBox2);
			this->groupBoxPM->Controls->Add(this->groupBox1);
			this->groupBoxPM->Controls->Add(this->pmPreview);
			this->groupBoxPM->Location = System::Drawing::Point(12, 158);
			this->groupBoxPM->Name = L"groupBoxPM";
			this->groupBoxPM->Size = System::Drawing::Size(533, 140);
			this->groupBoxPM->TabIndex = 8;
			this->groupBoxPM->TabStop = false;
			this->groupBoxPM->Text = L"PSF (PhotonMAX Camera)";
			// 
			// pmROIGroupBox
			// 
			this->pmROIGroupBox->Controls->Add(this->pmROIYEndC);
			this->pmROIGroupBox->Controls->Add(this->pmROIYEnd);
			this->pmROIGroupBox->Controls->Add(this->pmROIYStart);
			this->pmROIGroupBox->Controls->Add(this->pmROIYStartC);
			this->pmROIGroupBox->Controls->Add(this->pmROIXEndC);
			this->pmROIGroupBox->Controls->Add(this->pmROIXEnd);
			this->pmROIGroupBox->Controls->Add(this->pmROIXStart);
			this->pmROIGroupBox->Controls->Add(this->pmROIXStartC);
			this->pmROIGroupBox->Location = System::Drawing::Point(156, 74);
			this->pmROIGroupBox->Name = L"pmROIGroupBox";
			this->pmROIGroupBox->Size = System::Drawing::Size(192, 55);
			this->pmROIGroupBox->TabIndex = 14;
			this->pmROIGroupBox->TabStop = false;
			this->pmROIGroupBox->Text = L"ROI";
			// 
			// pmROIYEndC
			// 
			this->pmROIYEndC->Location = System::Drawing::Point(145, 32);
			this->pmROIYEndC->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 511, 0, 0, 0 });
			this->pmROIYEndC->Name = L"pmROIYEndC";
			this->pmROIYEndC->Size = System::Drawing::Size(43, 20);
			this->pmROIYEndC->TabIndex = 18;
			this->pmROIYEndC->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 511, 0, 0, 0 });
			this->pmROIYEndC->ValueChanged += gcnew System::EventHandler(this, &MainForm::pmROIYEndC_ValueChanged);
			// 
			// pmROIYEnd
			// 
			this->pmROIYEnd->AutoSize = true;
			this->pmROIYEnd->Location = System::Drawing::Point(113, 36);
			this->pmROIYEnd->Name = L"pmROIYEnd";
			this->pmROIYEnd->Size = System::Drawing::Size(26, 13);
			this->pmROIYEnd->TabIndex = 6;
			this->pmROIYEnd->Text = L"End";
			this->pmROIYEnd->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// pmROIYStart
			// 
			this->pmROIYStart->AutoSize = true;
			this->pmROIYStart->Location = System::Drawing::Point(100, 13);
			this->pmROIYStart->Name = L"pmROIYStart";
			this->pmROIYStart->Size = System::Drawing::Size(39, 13);
			this->pmROIYStart->TabIndex = 5;
			this->pmROIYStart->Text = L"Y Start";
			this->pmROIYStart->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// pmROIYStartC
			// 
			this->pmROIYStartC->Location = System::Drawing::Point(145, 11);
			this->pmROIYStartC->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 511, 0, 0, 0 });
			this->pmROIYStartC->Name = L"pmROIYStartC";
			this->pmROIYStartC->Size = System::Drawing::Size(43, 20);
			this->pmROIYStartC->TabIndex = 17;
			this->pmROIYStartC->ValueChanged += gcnew System::EventHandler(this, &MainForm::pmROIYStartC_ValueChanged);
			// 
			// pmROIXEndC
			// 
			this->pmROIXEndC->Location = System::Drawing::Point(51, 32);
			this->pmROIXEndC->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 511, 0, 0, 0 });
			this->pmROIXEndC->Name = L"pmROIXEndC";
			this->pmROIXEndC->Size = System::Drawing::Size(43, 20);
			this->pmROIXEndC->TabIndex = 16;
			this->pmROIXEndC->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 511, 0, 0, 0 });
			this->pmROIXEndC->ValueChanged += gcnew System::EventHandler(this, &MainForm::pmROIXEndC_ValueChanged);
			// 
			// pmROIXEnd
			// 
			this->pmROIXEnd->AutoSize = true;
			this->pmROIXEnd->Location = System::Drawing::Point(19, 36);
			this->pmROIXEnd->Name = L"pmROIXEnd";
			this->pmROIXEnd->Size = System::Drawing::Size(26, 13);
			this->pmROIXEnd->TabIndex = 2;
			this->pmROIXEnd->Text = L"End";
			this->pmROIXEnd->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// pmROIXStart
			// 
			this->pmROIXStart->AutoSize = true;
			this->pmROIXStart->Location = System::Drawing::Point(6, 13);
			this->pmROIXStart->Name = L"pmROIXStart";
			this->pmROIXStart->Size = System::Drawing::Size(39, 13);
			this->pmROIXStart->TabIndex = 1;
			this->pmROIXStart->Text = L"X Start";
			this->pmROIXStart->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// pmROIXStartC
			// 
			this->pmROIXStartC->Location = System::Drawing::Point(51, 11);
			this->pmROIXStartC->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 511, 0, 0, 0 });
			this->pmROIXStartC->Name = L"pmROIXStartC";
			this->pmROIXStartC->Size = System::Drawing::Size(43, 20);
			this->pmROIXStartC->TabIndex = 15;
			this->pmROIXStartC->ValueChanged += gcnew System::EventHandler(this, &MainForm::pmROIXStartC_ValueChanged);
			// 
			// pmSaveButton
			// 
			this->pmSaveButton->Location = System::Drawing::Point(354, 19);
			this->pmSaveButton->Name = L"pmSaveButton";
			this->pmSaveButton->Size = System::Drawing::Size(77, 110);
			this->pmSaveButton->TabIndex = 19;
			this->pmSaveButton->Text = L"Save";
			this->pmSaveButton->UseVisualStyleBackColor = true;
			this->pmSaveButton->Click += gcnew System::EventHandler(this, &MainForm::pmSaveButton_Click);
			// 
			// pmGroupBox2
			// 
			this->pmGroupBox2->Controls->Add(this->pmGainControl);
			this->pmGroupBox2->Location = System::Drawing::Point(156, 19);
			this->pmGroupBox2->Name = L"pmGroupBox2";
			this->pmGroupBox2->Size = System::Drawing::Size(102, 55);
			this->pmGroupBox2->TabIndex = 12;
			this->pmGroupBox2->TabStop = false;
			this->pmGroupBox2->Text = L"Gain";
			// 
			// pmGainControl
			// 
			this->pmGainControl->Location = System::Drawing::Point(6, 22);
			this->pmGainControl->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4095, 0, 0, 0 });
			this->pmGainControl->Name = L"pmGainControl";
			this->pmGainControl->Size = System::Drawing::Size(88, 20);
			this->pmGainControl->TabIndex = 13;
			this->pmGainControl->ValueChanged += gcnew System::EventHandler(this, &MainForm::pmGainControl_ValueChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->pmExpTrackBar);
			this->groupBox1->Controls->Add(this->pmExpTextBox);
			this->groupBox1->Location = System::Drawing::Point(19, 19);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(131, 110);
			this->groupBox1->TabIndex = 9;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Exposure time (msec)";
			// 
			// pmExpTrackBar
			// 
			this->pmExpTrackBar->LargeChange = 100;
			this->pmExpTrackBar->Location = System::Drawing::Point(7, 51);
			this->pmExpTrackBar->Maximum = 10000;
			this->pmExpTrackBar->Minimum = 1;
			this->pmExpTrackBar->Name = L"pmExpTrackBar";
			this->pmExpTrackBar->Size = System::Drawing::Size(118, 45);
			this->pmExpTrackBar->TabIndex = 11;
			this->pmExpTrackBar->TickFrequency = 1000;
			this->pmExpTrackBar->Value = 1;
			this->pmExpTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::pmExpTrackBar_ValueChanged);
			// 
			// pmExpTextBox
			// 
			this->pmExpTextBox->Location = System::Drawing::Point(6, 22);
			this->pmExpTextBox->Name = L"pmExpTextBox";
			this->pmExpTextBox->Size = System::Drawing::Size(119, 20);
			this->pmExpTextBox->TabIndex = 10;
			this->pmExpTextBox->Text = L"100";
			this->pmExpTextBox->TextChanged += gcnew System::EventHandler(this, &MainForm::pmExpTextBox_TextChanged);
			// 
			// pmPreview
			// 
			this->pmPreview->Location = System::Drawing::Point(437, 19);
			this->pmPreview->Name = L"pmPreview";
			this->pmPreview->Size = System::Drawing::Size(77, 110);
			this->pmPreview->TabIndex = 20;
			this->pmPreview->Text = L"Preview";
			this->pmPreview->UseVisualStyleBackColor = true;
			this->pmPreview->Click += gcnew System::EventHandler(this, &MainForm::pmPreview_Click);
			// 
			// pmFrameGroupBox
			// 
			this->pmFrameGroupBox->Controls->Add(this->pmFrameControl);
			this->pmFrameGroupBox->Location = System::Drawing::Point(264, 19);
			this->pmFrameGroupBox->Name = L"pmFrameGroupBox";
			this->pmFrameGroupBox->Size = System::Drawing::Size(84, 55);
			this->pmFrameGroupBox->TabIndex = 14;
			this->pmFrameGroupBox->TabStop = false;
			this->pmFrameGroupBox->Text = L"Frames";
			// 
			// pmFrameControl
			// 
			this->pmFrameControl->Location = System::Drawing::Point(6, 22);
			this->pmFrameControl->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 65535, 0, 0, 0 });
			this->pmFrameControl->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->pmFrameControl->Name = L"pmFrameControl";
			this->pmFrameControl->Size = System::Drawing::Size(72, 20);
			this->pmFrameControl->TabIndex = 13;
			this->pmFrameControl->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(556, 310);
			this->Controls->Add(this->groupBoxPM);
			this->Controls->Add(this->groupBoxPL);
			this->Name = L"MainForm";
			this->Text = L"SFA Streaming";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MainForm::MainForm_FormClosed);
			this->groupBoxPL->ResumeLayout(false);
			this->plGainGroupBox->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->plGainControl))->EndInit();
			this->plExpGroupBox->ResumeLayout(false);
			this->plExpGroupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->plExpTrackBar))->EndInit();
			this->groupBoxPM->ResumeLayout(false);
			this->pmROIGroupBox->ResumeLayout(false);
			this->pmROIGroupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pmROIYEndC))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pmROIYStartC))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pmROIXEndC))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pmROIXStartC))->EndInit();
			this->pmGroupBox2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pmGainControl))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pmExpTrackBar))->EndInit();
			this->pmFrameGroupBox->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pmFrameControl))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void pmPreview_Click(System::Object^  sender, System::EventArgs^  e) {
		CameraPreview ^preview = gcnew CameraPreview;
		preview->Text = "PSF Stream";
		preview->Show();

		initpmCam();
		CameraParameters ^params = gcnew CameraParameters(preview, pmCam);

		MainForm ^frm = gcnew MainForm;
		Thread ^previewThread = gcnew Thread(
								gcnew ParameterizedThreadStart(frm,
									&MainForm::PreviewThread));
		previewThread->Start(params);
	}
private: System::Void pmExpTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	System::String ^v = System::Convert::ToString(pmExpTrackBar->Value);
	pmExpTextBox->Text = v;
}
private: System::Void pmSaveButton_Click(System::Object^  sender, System::EventArgs^  e) {
	initpmCam();
	short frames = System::Convert::ToInt16(pmFrameControl->Value);
	saveImage(pmCam, frames);
}
private: void saveImage(Camera *cam, short frames) {
	pmSaveDialog->Filter = "FITS file|*.fits";
	pmSaveDialog->Title = "Save image";
	System::Windows::Forms::DialogResult dr;
	dr = pmSaveDialog->ShowDialog();
	String ^dialogFp = pmSaveDialog->FileName;

	if (dr == System::Windows::Forms::DialogResult::OK) {
		if (frames == 1)
			captureAndSave(dialogFp, cam);
		else {
			short i = 1;
			String ^fn =
				System::IO::Path::GetDirectoryName(dialogFp) + "\\" +
				System::IO::Path::GetFileNameWithoutExtension(dialogFp);

			while (frames > 0) {
				String ^fp = fn + i.ToString() + ".fits";
				captureAndSave(fp, cam);

				frames--;
				i++;
			}
		}
	}
}
private: void captureAndSave(String ^fp, Camera *cam) {
	fitsfile *fptr;
	int fitstatus = 0, naxis = 2;
	long naxes[2], firstelem, nelements;
	const char *fn = (const char *)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fp).ToPointer());
	unsigned short *data = cam->getRawFrame();
	naxes[0] = cam->WX;
	naxes[1] = cam->WY;

	remove(fn);
	fits_create_file(&fptr, fn, &fitstatus);
	fits_create_img(fptr, USHORT_IMG, naxis, naxes, &fitstatus);
	firstelem = 1;
	nelements = cam->WX * cam->WY;
	fits_write_img(fptr, TUSHORT, firstelem, nelements, data, &fitstatus);
	fits_close_file(fptr, &fitstatus);
	delete data;
}
private: void initpmCam() {
	if (pmCam == NULL) {
		try {
			pmCam = new cPhotonMAX(100, 0, 0, 511, 0, 511);
		}
		catch (VNCCamera::CameraException &e) {
			std::string msg("Camera error, check connection: ");
			std::string emsg(e.what());
			std::string err = msg + emsg;

			String ^hErr = gcnew String(err.c_str());
			MessageBox::Show(hErr);
			delete hErr;
			pmCam = NULL;
			initpmCam();
		}
	}
}
private: void initplCam() {
	if (plCam == NULL) {
		try {
			plCam = new cPixeLINK(2592, 1944);
		}
		catch (PixeLINK::CameraException ^e) {
			std::string msg("Camera error, check connection.");

			String ^hErr = gcnew String(msg.c_str());
			MessageBox::Show(hErr);
			delete hErr;
			plCam = NULL;
			initplCam();
		}
	}
}
private: System::Void MainForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
	delete pmCam;
	delete plCam;
}
private: System::Void pmExpTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	String ^exp = pmExpTextBox->Text;
	unsigned int expTime = Convert::ToUInt32(exp, 10);
	pmCam->setExposureTime(expTime);
}
private: System::Void pmGainControl_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	Decimal ^v = pmGainControl->Value;
	unsigned short gain = Convert::ToUInt16(v);
	pmCam->setGain(gain);
}
private: System::Void pmROIXStartC_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	updateROI(pmCam);
}
private: System::Void pmROIYStartC_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	updateROI(pmCam);
}
private: System::Void pmROIXEndC_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	updateROI(pmCam);
}
private: System::Void pmROIYEndC_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	updateROI(pmCam);
}
private: void updateROI(Camera *cam) {
	unsigned short sx = Convert::ToUInt16(pmROIXStartC->Value);
	unsigned short sy = Convert::ToUInt16(pmROIYStartC->Value);
	unsigned short ex = Convert::ToUInt16(pmROIXEndC->Value);
	unsigned short ey = Convert::ToUInt16(pmROIYEndC->Value);
	cam->setROI(sx, sy, ex, ey);
}
private: System::Void plPreviewButton_Click(System::Object^  sender, System::EventArgs^  e) {
	initplCam();

	//CameraPreview ^preview = gcnew CameraPreview(plCam->WX, plCam->WY);
	CameraPreview ^preview = gcnew CameraPreview(800, 600);
	preview->Text = "Pupil Stream";
	preview->Show();

	CameraParameters ^params = gcnew CameraParameters(preview, plCam);

	MainForm ^frm = gcnew MainForm;
	Thread ^previewThread = gcnew Thread(
		gcnew ParameterizedThreadStart(frm,
			&MainForm::PreviewThread));
	previewThread->Start(params);
}
private: System::Void plExpTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	System::String ^v = System::Convert::ToString(plExpTrackBar->Value);
	plExpTextBox->Text = v;
}
private: System::Void plExpTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	String ^exp = plExpTextBox->Text;
	unsigned int expTime = Convert::ToUInt32(exp, 10);
	plCam->setExposureTime(expTime);
}
private: System::Void plGainControl_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	float g = System::Convert::ToDouble(plGainControl->Value);
	plCam->setGain(g);
}
private: System::Void plSaveButton_Click(System::Object^  sender, System::EventArgs^  e) {
	initplCam();
	saveImage(plCam, 1);
}
};
}