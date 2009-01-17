// Copyright (C) 2003-2008 Dolphin Project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official SVN repository and contact information can be found at
// http://code.google.com/p/dolphin-emu/


#include "Config.h"
#include "ConfigDlg.h"

BEGIN_EVENT_TABLE(ConfigDialog, wxDialog)
EVT_BUTTON(wxID_OK, ConfigDialog::SettingsChanged)
EVT_CHECKBOX(ID_ENABLE_HLE_AUDIO, ConfigDialog::SettingsChanged)
EVT_CHECKBOX(ID_ENABLE_DTK_MUSIC, ConfigDialog::SettingsChanged)
EVT_CHECKBOX(ID_ENABLE_THROTTLE, ConfigDialog::SettingsChanged)
END_EVENT_TABLE()

ConfigDialog::ConfigDialog(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	// Load config settings
	g_Config.Load();

	// Center window
	CenterOnParent();

	m_OK = new wxButton(this, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator);

	// Create items
	m_buttonEnableHLEAudio = new wxCheckBox(this, ID_ENABLE_HLE_AUDIO, wxT("Enable HLE Audio"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator);
	m_buttonEnableDTKMusic = new wxCheckBox(this, ID_ENABLE_DTK_MUSIC, wxT("Enable DTK Music"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator);
	m_buttonEnableThrottle = new wxCheckBox(this, ID_ENABLE_THROTTLE, wxT("Enable Other Audio (Throttle)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator);

	// Update checkboxes
	m_buttonEnableHLEAudio->SetValue(g_Config.m_EnableHLEAudio ? true : false);
	m_buttonEnableDTKMusic->SetValue(g_Config.m_EnableDTKMusic ? true : false);
	m_buttonEnableThrottle->SetValue(g_Config.m_EnableThrottle ? true : false);

	// Add tooltips
	m_buttonEnableHLEAudio->SetToolTip(wxT("This is the most common sound type"));
	m_buttonEnableDTKMusic->SetToolTip(wxT("This is sometimes used to play music tracks from the disc"));
	m_buttonEnableThrottle->SetToolTip(wxT("This is sometimes used together with pre-rendered movies.\n"
		"Disabling this also disables the speed throttle which this causes,\n"
		"meaning that there will be no upper limit on your FPS."));

	// Create sizer and add items to dialog
	wxBoxSizer *sMain = new wxBoxSizer(wxVERTICAL);
	wxStaticBoxSizer *sbSettings = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Sound Settings"));
	sbSettings->Add(m_buttonEnableHLEAudio, 0, wxALL, 5);
	sbSettings->Add(m_buttonEnableDTKMusic, 0, wxALL, 5);
	sbSettings->Add(m_buttonEnableThrottle, 0, wxALL, 5);
	sMain->Add(sbSettings, 0, wxEXPAND|wxALL, 5);
	wxBoxSizer *sButtons = new wxBoxSizer(wxHORIZONTAL);
	sButtons->Add(150, 0); // Lazy way to make the dialog as wide as we want it
	sButtons->Add(m_OK, 0, wxALL, 5);
	sMain->Add(sButtons, 0, wxEXPAND);
	this->SetSizerAndFit(sMain);
}

ConfigDialog::~ConfigDialog()
{
}

void ConfigDialog::SettingsChanged(wxCommandEvent& event)
{
	g_Config.m_EnableHLEAudio = m_buttonEnableHLEAudio->GetValue();
	g_Config.m_EnableDTKMusic = m_buttonEnableDTKMusic->GetValue();
	g_Config.m_EnableThrottle = m_buttonEnableThrottle->GetValue();
	g_Config.Save();

	if (event.GetId() == wxID_OK)
		EndModal(wxID_OK);
}
