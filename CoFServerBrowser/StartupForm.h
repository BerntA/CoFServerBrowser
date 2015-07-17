#pragma once

#include "IClientMode.h"

namespace CoFServerBrowser {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for StartupForm
	/// </summary>
	public ref class StartupForm : public System::Windows::Forms::Form
	{
	public:
		StartupForm(void)
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
		~StartupForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  lblVersion;
	private: System::Windows::Forms::Timer^  timFade;
	private: System::Windows::Forms::Timer^  timLaunchMain;
	private: System::Windows::Forms::Timer^  timFadeOut;

	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		bool closeToMain;
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(StartupForm::typeid));
			this->lblVersion = (gcnew System::Windows::Forms::Label());
			this->timFade = (gcnew System::Windows::Forms::Timer(this->components));
			this->timLaunchMain = (gcnew System::Windows::Forms::Timer(this->components));
			this->timFadeOut = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// lblVersion
			// 
			this->lblVersion->AutoSize = true;
			this->lblVersion->BackColor = System::Drawing::Color::Transparent;
			this->lblVersion->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblVersion->ForeColor = System::Drawing::Color::White;
			this->lblVersion->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->lblVersion->Location = System::Drawing::Point(507, 233);
			this->lblVersion->Name = L"lblVersion";
			this->lblVersion->Size = System::Drawing::Size(92, 15);
			this->lblVersion->TabIndex = 0;
			this->lblVersion->Text = L"Version: 1.0.0.2";
			this->lblVersion->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// timFade
			// 
			this->timFade->Interval = 50;
			this->timFade->Tick += gcnew System::EventHandler(this, &StartupForm::timFade_Tick);
			// 
			// timLaunchMain
			// 
			this->timLaunchMain->Interval = 1200;
			this->timLaunchMain->Tick += gcnew System::EventHandler(this, &StartupForm::timLaunchMain_Tick);
			// 
			// timFadeOut
			// 
			this->timFadeOut->Interval = 50;
			this->timFadeOut->Tick += gcnew System::EventHandler(this, &StartupForm::timFadeOut_Tick);
			// 
			// StartupForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Black;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(600, 250);
			this->ControlBox = false;
			this->Controls->Add(this->lblVersion);
			this->Cursor = System::Windows::Forms::Cursors::WaitCursor;
			this->DoubleBuffered = true;
			this->ForeColor = System::Drawing::Color::Black;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"StartupForm";
			this->Opacity = 0;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"CoF Server Browser";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &StartupForm::StartupForm_FormClosing);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &StartupForm::StartupForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &StartupForm::StartupForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void timFade_Tick(System::Object^  sender, System::EventArgs^  e)
	{
		if (this->Opacity < 1)
			this->Opacity += .05;
		else
		{
			this->Opacity = 1;
			timFade->Enabled = false;
			timLaunchMain->Enabled = true;
		}
	}

	private: System::Void StartupForm_Load(System::Object^  sender, System::EventArgs^  e)
	{
		timFade->Enabled = true;
		closeToMain = false;
		FMODManager()->PlaySound("sound/music/startup.wav");
	}

	private: System::Void timLaunchMain_Tick(System::Object^  sender, System::EventArgs^  e)
	{
		timLaunchMain->Enabled = false;
		timFadeOut->Enabled = true;
	}

	private: System::Void timFadeOut_Tick(System::Object^  sender, System::EventArgs^  e)
	{
		if (this->Opacity > 0)
			this->Opacity -= .05;
		else
		{
			this->Opacity = 0;
			timFadeOut->Enabled = false;
			ClientMode->StartMainForm(true);
			closeToMain = true;
			this->Close();
		}
	}
	private: System::Void StartupForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		if (!closeToMain)
			ClientMode->ExitApplication();
	}
private: System::Void StartupForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
	if (!closeToMain)
		ClientMode->ExitApplication();
}
};
}
