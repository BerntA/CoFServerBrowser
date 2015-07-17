#pragma once

#include "IClientMode.h"
#include "CommCtrl.h"
#include "Stringapiset.h"
#include "steam_api.h"
#include <shlobj.h>
#include <shlwapi.h>
#include <objbase.h>
#include "Shellapi.h"
#include "Wingdi.h"
#include "PlayerInfoForm.h"

namespace CoFServerBrowser {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Collections::Generic;
	using namespace System::Diagnostics;

	/// <summary>
	/// Summary for ServerBrowserForm
	/// </summary>
	public ref class ServerBrowserForm : public System::Windows::Forms::Form
	{
	public:
		static ServerBrowserForm^ mainForm;

		ServerBrowserForm(void)
		{
			InitializeComponent();
			mainForm = this;
			m_iActiveMenuStripItem = -1;
			pszServerItems = gcnew List<KeyValuePair<uint32, uint16>>();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ServerBrowserForm()
		{
			if (components)
			{
				delete components;
			}
		}

		int m_iActiveMenuStripItem;

	private: System::Windows::Forms::Timer^  timFadeIn;
	private: System::Windows::Forms::Timer^  timFadeOut;
	private: System::Windows::Forms::ListView^  serverList;
	private: System::Windows::Forms::ColumnHeader^  columnName;
	private: System::Windows::Forms::ColumnHeader^  columnPlayers;
	private: System::Windows::Forms::ColumnHeader^  columnPing;
	private: System::Windows::Forms::ColumnHeader^  columnMap;
	private: System::Windows::Forms::ColumnHeader^  columnIp;
	private: System::Windows::Forms::MenuStrip^  menuItemList;

	private: System::Windows::Forms::ToolStripMenuItem^  playMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  refreshMenuItem;
	private: System::Windows::Forms::ContextMenuStrip^  menuStrip;
	private: System::Windows::Forms::ToolStripMenuItem^  connectMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  showPlayersMenuItem;
	private: System::Windows::Forms::ImageList^  imageList;
	private: System::Windows::Forms::ColumnHeader^  columnPassword;




	private: System::ComponentModel::IContainer^  components;

	protected:

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ServerBrowserForm::typeid));
			this->timFadeIn = (gcnew System::Windows::Forms::Timer(this->components));
			this->timFadeOut = (gcnew System::Windows::Forms::Timer(this->components));
			this->serverList = (gcnew System::Windows::Forms::ListView());
			this->columnPassword = (gcnew System::Windows::Forms::ColumnHeader(0));
			this->columnName = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnPlayers = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnPing = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnMap = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnIp = (gcnew System::Windows::Forms::ColumnHeader());
			this->imageList = (gcnew System::Windows::Forms::ImageList(this->components));
			this->menuItemList = (gcnew System::Windows::Forms::MenuStrip());
			this->playMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->refreshMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->connectMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->showPlayersMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuItemList->SuspendLayout();
			this->menuStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// timFadeIn
			// 
			this->timFadeIn->Interval = 35;
			this->timFadeIn->Tick += gcnew System::EventHandler(this, &ServerBrowserForm::timFadeIn_Tick);
			// 
			// timFadeOut
			// 
			this->timFadeOut->Interval = 25;
			this->timFadeOut->Tick += gcnew System::EventHandler(this, &ServerBrowserForm::timFadeOut_Tick);
			// 
			// serverList
			// 
			this->serverList->Activation = System::Windows::Forms::ItemActivation::OneClick;
			this->serverList->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(31)));
			this->serverList->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"serverList.BackgroundImage")));
			this->serverList->BackgroundImageTiled = true;
			this->serverList->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->serverList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(6) {
				this->columnPassword,
					this->columnName, this->columnPlayers, this->columnPing, this->columnMap, this->columnIp
			});
			this->serverList->ForeColor = System::Drawing::Color::White;
			this->serverList->FullRowSelect = true;
			this->serverList->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->serverList->Location = System::Drawing::Point(2, 27);
			this->serverList->MultiSelect = false;
			this->serverList->Name = L"serverList";
			this->serverList->Size = System::Drawing::Size(979, 530);
			this->serverList->SmallImageList = this->imageList;
			this->serverList->TabIndex = 1;
			this->serverList->TileSize = System::Drawing::Size(10, 10);
			this->serverList->UseCompatibleStateImageBehavior = false;
			this->serverList->View = System::Windows::Forms::View::Details;
			this->serverList->DoubleClick += gcnew System::EventHandler(this, &ServerBrowserForm::serverList_DoubleClick);
			this->serverList->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &ServerBrowserForm::serverList_KeyDown);
			this->serverList->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &ServerBrowserForm::serverList_MouseDown);
			// 
			// columnPassword
			// 
			this->columnPassword->Text = L"";
			this->columnPassword->Width = 30;
			// 
			// columnName
			// 
			this->columnName->Text = L"Name";
			this->columnName->Width = 400;
			// 
			// columnPlayers
			// 
			this->columnPlayers->Text = L"Players";
			this->columnPlayers->Width = 80;
			// 
			// columnPing
			// 
			this->columnPing->Text = L"Ping";
			this->columnPing->Width = 80;
			// 
			// columnMap
			// 
			this->columnMap->Text = L"Map";
			this->columnMap->Width = 418;
			// 
			// columnIp
			// 
			this->columnIp->Text = L"IP Address";
			this->columnIp->Width = 400;
			// 
			// imageList
			// 
			this->imageList->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageList.ImageStream")));
			this->imageList->TransparentColor = System::Drawing::Color::Transparent;
			this->imageList->Images->SetKeyName(0, L"password.png");
			this->imageList->Images->SetKeyName(1, L"password.jpg");
			this->imageList->Images->SetKeyName(2, L"transparency.jpg");
			// 
			// menuItemList
			// 
			this->menuItemList->BackColor = System::Drawing::Color::White;
			this->menuItemList->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->menuItemList->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->playMenuItem, this->refreshMenuItem,
					this->aboutMenuItem, this->helpMenuItem
			});
			this->menuItemList->Location = System::Drawing::Point(0, 0);
			this->menuItemList->Name = L"menuItemList";
			this->menuItemList->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
			this->menuItemList->Size = System::Drawing::Size(980, 24);
			this->menuItemList->TabIndex = 2;
			this->menuItemList->Text = L"menuContext";
			// 
			// playMenuItem
			// 
			this->playMenuItem->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->playMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"playMenuItem.Image")));
			this->playMenuItem->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->playMenuItem->ImageTransparentColor = System::Drawing::Color::Transparent;
			this->playMenuItem->Name = L"playMenuItem";
			this->playMenuItem->Size = System::Drawing::Size(57, 20);
			this->playMenuItem->Text = L"Play";
			this->playMenuItem->Click += gcnew System::EventHandler(this, &ServerBrowserForm::playMenuItem_Click);
			// 
			// refreshMenuItem
			// 
			this->refreshMenuItem->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->refreshMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"refreshMenuItem.Image")));
			this->refreshMenuItem->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->refreshMenuItem->Name = L"refreshMenuItem";
			this->refreshMenuItem->Size = System::Drawing::Size(74, 20);
			this->refreshMenuItem->Text = L"Refresh";
			this->refreshMenuItem->Click += gcnew System::EventHandler(this, &ServerBrowserForm::refreshMenuItem_Click);
			// 
			// aboutMenuItem
			// 
			this->aboutMenuItem->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->aboutMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"aboutMenuItem.Image")));
			this->aboutMenuItem->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->aboutMenuItem->Name = L"aboutMenuItem";
			this->aboutMenuItem->Size = System::Drawing::Size(68, 20);
			this->aboutMenuItem->Text = L"About";
			this->aboutMenuItem->Click += gcnew System::EventHandler(this, &ServerBrowserForm::aboutMenuItem_Click);
			// 
			// helpMenuItem
			// 
			this->helpMenuItem->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->helpMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"helpMenuItem.Image")));
			this->helpMenuItem->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->helpMenuItem->Name = L"helpMenuItem";
			this->helpMenuItem->Size = System::Drawing::Size(60, 20);
			this->helpMenuItem->Text = L"Help";
			this->helpMenuItem->Click += gcnew System::EventHandler(this, &ServerBrowserForm::helpMenuItem_Click);
			// 
			// menuStrip
			// 
			this->menuStrip->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->connectMenuItem, this->showPlayersMenuItem });
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
			this->menuStrip->ShowItemToolTips = false;
			this->menuStrip->Size = System::Drawing::Size(169, 48);
			// 
			// connectMenuItem
			// 
			this->connectMenuItem->BackColor = System::Drawing::SystemColors::Control;
			this->connectMenuItem->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->connectMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"connectMenuItem.Image")));
			this->connectMenuItem->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->connectMenuItem->Name = L"connectMenuItem";
			this->connectMenuItem->Size = System::Drawing::Size(168, 22);
			this->connectMenuItem->Text = L"Connect to Server";
			this->connectMenuItem->Click += gcnew System::EventHandler(this, &ServerBrowserForm::connectMenuItem_Click);
			// 
			// showPlayersMenuItem
			// 
			this->showPlayersMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"showPlayersMenuItem.Image")));
			this->showPlayersMenuItem->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->showPlayersMenuItem->Name = L"showPlayersMenuItem";
			this->showPlayersMenuItem->Size = System::Drawing::Size(168, 22);
			this->showPlayersMenuItem->Text = L"Show Players";
			this->showPlayersMenuItem->Click += gcnew System::EventHandler(this, &ServerBrowserForm::showPlayersMenuItem_Click);
			// 
			// ServerBrowserForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Black;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(980, 558);
			this->Controls->Add(this->serverList);
			this->Controls->Add(this->menuItemList);
			this->DoubleBuffered = true;
			this->ForeColor = System::Drawing::Color::White;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuItemList;
			this->MaximizeBox = false;
			this->Name = L"ServerBrowserForm";
			this->Opacity = 0;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"CoF Server Browser";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &ServerBrowserForm::ServerBrowserForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &ServerBrowserForm::ServerBrowserForm_Load);
			this->menuItemList->ResumeLayout(false);
			this->menuItemList->PerformLayout();
			this->menuStrip->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	public:
		List<KeyValuePair<uint32, uint16>> ^pszServerItems;

		// Clear our server list!
		void RefreshServerList(void)
		{
			serverList->Items->Clear();
			pszServerItems->Clear();
		}

		// Populate our list with servers!
		void AddServerItem(bool bNeedPassword, const char *Name, const char *Map, const char *Players, const char *Ping, const char *Ip, uint32 ipAddress, uint16 port)
		{
			System::String ^name = gcnew String(Name);
			System::String ^map = gcnew String(Map);
			System::String ^ip = gcnew String(Ip);
			System::String ^plrs = gcnew String(Players);
			System::String ^ping = gcnew String(Ping);

			ListViewItem^ item = gcnew ListViewItem(gcnew array < String^ > { "", name, plrs, ping, map, ip });
			item->ImageIndex = (bNeedPassword ? 1 : 2);
			serverList->Items->Add(item);
			// We need the raw ip and port splitted in order to get the player info @ steam api.
			KeyValuePair<uint32, uint16> pair(ipAddress, port);
			pszServerItems->Add(pair);
		}

	private: System::Void timFadeOut_Tick(System::Object^  sender, System::EventArgs^  e)
	{
		if (Opacity > 0)
			Opacity -= .05;
		else
		{
			Opacity = 0;
			timFadeOut->Enabled = false;
			ClientMode->ExitApplication();
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

	private: System::Void ServerBrowserForm_Load(System::Object^  sender, System::EventArgs^  e)
	{
		timFadeIn->Enabled = true;

		char szFile[256];
		_snprintf_s(szFile, 256, "%s/settings.txt", ClientMode->GetStartupPath());
		System::String ^filePath = gcnew String(szFile);

		// We generate the default settings file to load the custom startup cmds and default ones dependent on your resolution and window preference, etc...
		if (!File::Exists(filePath))
		{
			RECT actualDesktop;
			GetWindowRect(GetDesktopWindow(), &actualDesktop);

			StreamWriter^ sw = gcnew StreamWriter(filePath);
			sw->WriteLine("-no3dmenu");
			sw->WriteLine("-fullscreen");
			// 16:10 or 16:9 = widescreen.
			if (ClientMode->IsWideScreen(actualDesktop.right, actualDesktop.bottom))
				sw->WriteLine("-widescreen");
			sw->WriteLine("-w " + actualDesktop.right.ToString());
			sw->WriteLine("-h " + actualDesktop.bottom.ToString());
			sw->Close();
		}
	}

	private: System::Void ServerBrowserForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
	{
		e->Cancel = true;
		timFadeOut->Enabled = true;
	}

	private: System::Void serverList_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
	{
		if (e->KeyCode == Keys::F5)
			ClientMode->RequestServerList();
	}

	private: System::Void serverList_DoubleClick(System::Object^  sender, System::EventArgs^  e)
	{
		if (serverList->SelectedItems->Count)
		{
			char szIP[200];
			_snprintf_s(szIP, 200, "%s", serverList->SelectedItems[0]->SubItems[5]->Text);
			ClientMode->RunProgram(szIP);
		}
	}

	private: System::Void helpMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		MessageBox::Show("You can use the F5 shortcut to update/refresh the server list.\nThe Play button in the context menu allows you to open the game right away, this has been added to bypass the launcher and allowing you to start CoF with unique launch options like changing your port number for online play.\n\nBecause I bypass the launcher I have no idea which resolution you want to have which is why I generate a file in the .exe's directory named 'settings.txt', this file contains the default startup params (custom) for CoF.\nBy default the resolution will be set to your primary desktop resolution and it will be set to fullscreen.\nTo change this open up the settings.txt file and change the -w & -h manually.\nYou can also add your own startup cmds here!\n\nTo join a server you have to double click an item in the server list\nYou can also join servers in this app while CoF is running, it will redirect the connection to the game and you will auto-connect to the new server!\n\nYou can also right click any item in the server list, this will pop up a context menu which allows you to click on 'Connect to Server' or 'Show Players'\nIf you click on 'Show Players' you'll be able to see all the active players on the server you selected, to quick refresh the list click F5, to quick close click ESC!\n\nHave fun!\n", "Instructions", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	private: System::Void aboutMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		MessageBox::Show("This program was written in C++ by Bernt Andreas Eide, I was sick of standing idle for so long after the standalone release/steampipe updates which broke the integrated server browser for CoF.\nNow you're finally able to see active servers for CoF.\n\nUnfortunately it isn't possible to host dedicated servers at this time because the programmer for CoF did some ineffective donation checks on the server side which ends up in the server crashing when there's no client in it (host). I've tried to use fakeclients/bots using third party plugins but this didn't solve the issue. One can only wish for the devs to fix this at some point, if it is possible.\n\nThe source code for this program is available at my GitHub profile 'BerntA' if you want to modify it or use it for something else.\n\nOther Notable Credits:\nArvuti - CoF Art(startup screen img)\nTeam Psykskallar - CoF Devs\nJoshikumako - Testing\n", "About", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	private: System::Void playMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		ClientMode->RunProgram(NULL);
	}

	private: System::Void refreshMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		ClientMode->RequestServerList();
	}

	private: System::Void serverList_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		// If we right click and we're within an item in the list we'll show the context menu!
		if (e->Button == System::Windows::Forms::MouseButtons::Right)
		{
			Point localPoint = serverList->PointToClient(Cursor->Position);
			ListViewItem ^item = serverList->GetItemAt(localPoint.X, localPoint.Y);
			if (item)
			{
				menuStrip->Show(Cursor->Position);
				menuStrip->Visible = true;
				m_iActiveMenuStripItem = item->Index;
				return;
			}
		}

		m_iActiveMenuStripItem = -1;
		menuStrip->Visible = false;
	}

	private: System::Void connectMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (serverList->SelectedItems->Count)
		{
			char szIP[200];
			_snprintf_s(szIP, 200, "%s", serverList->SelectedItems[0]->SubItems[5]->Text);
			ClientMode->RunProgram(szIP);
		}
	}

	private: System::Void showPlayersMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (serverList->SelectedItems->Count)
		{
			if (m_iActiveMenuStripItem != -1)
				PlayerInfoForm::playerInfoForm->ShowPlayerList(pszServerItems[m_iActiveMenuStripItem].Key, pszServerItems[m_iActiveMenuStripItem].Value);
		}
	}
	};
}