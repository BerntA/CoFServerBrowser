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
	/// Summary for PlayerInfoForm
	/// </summary>
	public ref class PlayerInfoForm : public System::Windows::Forms::Form
	{
	public:
		static PlayerInfoForm ^playerInfoForm;

		uint32 _ipAddress;
		uint16 _port;
		PlayerInfoForm(void)
		{
			InitializeComponent();
			playerInfoForm = this;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PlayerInfoForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListView^  playerList;
	protected:

	protected:
	private: System::Windows::Forms::ColumnHeader^  columnName;
	private: System::Windows::Forms::ColumnHeader^  columnScore;
	private: System::Windows::Forms::ColumnHeader^  columnTime;
	private: System::Windows::Forms::Timer^  timFadeIn;
	private: System::Windows::Forms::Timer^  timFadeOut;
	private: System::ComponentModel::IContainer^  components;



	private:
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(PlayerInfoForm::typeid));
			this->playerList = (gcnew System::Windows::Forms::ListView());
			this->columnName = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnScore = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnTime = (gcnew System::Windows::Forms::ColumnHeader());
			this->timFadeIn = (gcnew System::Windows::Forms::Timer(this->components));
			this->timFadeOut = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// playerList
			// 
			this->playerList->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
				static_cast<System::Int32>(static_cast<System::Byte>(32)));
			this->playerList->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->playerList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {
				this->columnName, this->columnScore,
					this->columnTime
			});
			this->playerList->ForeColor = System::Drawing::Color::White;
			this->playerList->FullRowSelect = true;
			this->playerList->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->playerList->HoverSelection = true;
			this->playerList->Location = System::Drawing::Point(2, 1);
			this->playerList->MultiSelect = false;
			this->playerList->Name = L"playerList";
			this->playerList->Size = System::Drawing::Size(281, 364);
			this->playerList->TabIndex = 0;
			this->playerList->UseCompatibleStateImageBehavior = false;
			this->playerList->View = System::Windows::Forms::View::Details;
			this->playerList->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &PlayerInfoForm::playerList_KeyDown);
			// 
			// columnName
			// 
			this->columnName->Text = L"Name";
			this->columnName->Width = 102;
			// 
			// columnScore
			// 
			this->columnScore->Text = L"Score";
			this->columnScore->Width = 67;
			// 
			// columnTime
			// 
			this->columnTime->Text = L"Time";
			this->columnTime->Width = 109;
			// 
			// timFadeIn
			// 
			this->timFadeIn->Interval = 10;
			this->timFadeIn->Tick += gcnew System::EventHandler(this, &PlayerInfoForm::timFadeIn_Tick);
			// 
			// timFadeOut
			// 
			this->timFadeOut->Interval = 15;
			this->timFadeOut->Tick += gcnew System::EventHandler(this, &PlayerInfoForm::timFadeOut_Tick);
			// 
			// PlayerInfoForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
				static_cast<System::Int32>(static_cast<System::Byte>(32)));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(284, 366);
			this->Controls->Add(this->playerList);
			this->DoubleBuffered = true;
			this->ForeColor = System::Drawing::Color::White;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"PlayerInfoForm";
			this->Opacity = 0;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Player Info";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &PlayerInfoForm::PlayerInfoForm_FormClosing);
			this->ResumeLayout(false);

		}
#pragma endregion
	public:
		void AddPlayerInfo(const char *szName, int score, float time)
		{
			// Generate our time played string. (the float is in sec)
			float timePlayed = time;
			float hoursPlayed = 0, minutesPlayed = 0, secondsPlayed = 0;

			while (timePlayed >= 3600) // 3600 sec in an hour.
			{
				timePlayed -= 3600;
				hoursPlayed++;
			}

			while (timePlayed >= 60) // 60 sec in a min.
			{
				timePlayed -= 60;
				minutesPlayed++;
			}

			secondsPlayed = timePlayed;
			secondsPlayed = round(secondsPlayed); // Let's round up to an even number... *lazy*

			System::String ^name = gcnew String(szName);
			ListViewItem^ item = gcnew ListViewItem(gcnew array < String^ > { name, score.ToString(), (hoursPlayed.ToString() + "Hr " + minutesPlayed.ToString() + "Min " + secondsPlayed.ToString() + "Sec") });
			playerList->Items->Add(item);
		}

		void ShowPlayerList(uint32 ip, uint16 port)
		{
			playerList->Items->Clear();

			if (!Visible)
			{
				Visible = true;
				timFadeIn->Enabled = true;
			}

			ClientMode->RequestPlayerInfo(ip, port);
			BringToFront();

			_ipAddress = ip;
			_port = port;
		}

	private: System::Void timFadeOut_Tick(System::Object^  sender, System::EventArgs^  e)
	{
		if (Opacity > 0)
			Opacity -= .05;
		else
		{
			Opacity = 0;
			timFadeOut->Enabled = false;
			Visible = false;
		}
	}

	private: System::Void timFadeIn_Tick(System::Object^  sender, System::EventArgs^  e)
	{
		if (Opacity < 1)
			Opacity += .05;
		else
		{
			Opacity = 1;
			timFadeIn->Enabled = false;
		}
	}

	private: System::Void PlayerInfoForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
	{
		e->Cancel = true;
		timFadeOut->Enabled = true;
	}

	private: System::Void playerList_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
	{
		if (e->KeyCode == Keys::F5)
			ShowPlayerList(_ipAddress, _port);
		else if (e->KeyCode == Keys::Escape)
			timFadeOut->Enabled = true;
	}
	};
}
