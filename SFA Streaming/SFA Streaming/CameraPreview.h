#pragma once

#include <stdio.h>

namespace VNCTest {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for CameraPreview
	/// </summary>
	public ref class CameraPreview : public System::Windows::Forms::Form
	{
	public:
		CameraPreview()
		{
			InitializeComponent();
		}

		CameraPreview(int sx, int sy)
		{
			sX = sx;
			sY = sy;
			InitializeComponent();
		}

		void updatePreview(Image ^im) {
			previewBox->Image = im;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CameraPreview()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  previewBox;
	protected:

	protected:

	private:
		int sX = 512, sY = 512;

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
			this->previewBox = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->previewBox))->BeginInit();
			this->SuspendLayout();
			// 
			// previewBox
			// 
			this->previewBox->Location = System::Drawing::Point(1, 1);
			this->previewBox->Name = L"previewBox";
			this->previewBox->Size = System::Drawing::Size(sX, sY);
			this->previewBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->previewBox->TabIndex = 0;
			this->previewBox->TabStop = false;
			// 
			// CameraPreview
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(sX + 2, sY + 2);
			this->Controls->Add(this->previewBox);
			this->Name = L"CameraPreview";
			this->Text = L"CameraPreview";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &CameraPreview::CameraPreview_FormClosed);
			this->Load += gcnew System::EventHandler(this, &CameraPreview::CameraPreview_Load);
			this->Shown += gcnew System::EventHandler(this, &CameraPreview::CameraPreview_Shown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->previewBox))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void CameraPreview_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void CameraPreview_Shown(System::Object^  sender, System::EventArgs^  e) {
		// Shown
	}
	private: System::Void CameraPreview_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
		// Closed
	}
	};
}
