#include "PrecompiledHeader.hpp"
#include "Program\App\HLCamEditorApp.hpp"
#include "Program\Dialogs\Main\HLCamEditorDialog.hpp"
#include "afxdialogex.h"

#include <memory>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace
{
	namespace ItemType
	{
		enum Type
		{
			Camera,
			Trigger,
		};
	}

	namespace ValueType
	{
		enum Type
		{
			FOV,
			Speed,
			PositionX,
			PositionY,
			PositionZ,
			AngleX,
			AngleY,
			AngleZ,
			PlaneType,
			
			LookType,
			TriggerType,
			Name,

			LookType_AtPlayer,
			LookType_AtAngle,
			TriggerType_ByTrigger,
			TriggerType_ByName,
		};
	}
}

HLCamEditorDialog::HLCamEditorDialog(CWnd* parent)
	: CDialogEx(IDD_HLCAMEDITOR_DIALOG, parent)
{
	Icon = AfxGetApp()->LoadIconA(IDR_MAINFRAME);
}

HLCamEditorDialog::~HLCamEditorDialog()
{
	
}

BEGIN_MESSAGE_MAP(HLCamEditorDialog, CDialogEx)
	ON_WM_GETMINMAXINFO()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, &OnPropertyGridItemChanged)
	ON_WM_CLOSE()
	ON_WM_SYSCOMMAND()
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &HLCamEditorDialog::OnTvnSelchangedTree1)
END_MESSAGE_MAP()

BOOL HLCamEditorDialog::OnInitDialog()
{
	__super::OnInitDialog();

	SetIcon(Icon, true);
	SetIcon(Icon, false);

	{
		auto testprop = new CMFCPropertyGridProperty("ID", COleVariant(0l));
		testprop->Enable(false);

		PropertyGrid.AddProperty(testprop);
	}

	{
		auto testprop = new CMFCPropertyGridProperty("Name", "");
		testprop->AllowEdit(true);

		testprop->SetData(ValueType::Name);

		PropertyGrid.AddProperty(testprop);
	}

	{
		auto testprop = new CMFCPropertyGridProperty("Activate type", "");
		testprop->AddOption("By trigger");
		testprop->AddOption("By name");

		testprop->AllowEdit(false);

		testprop->SetData(ValueType::TriggerType);

		PropertyGrid.AddProperty(testprop);
	}

	{
		auto testprop = new CMFCPropertyGridProperty("Lock axis", "");
		testprop->AddOption("None");
		testprop->AddOption("Horizontal");
		testprop->AddOption("Vertical");

		testprop->AllowEdit(false);

		testprop->SetData(ValueType::PlaneType);

		PropertyGrid.AddProperty(testprop);
	}

	{
		auto testprop = new CMFCPropertyGridProperty("Look at player", "");
		testprop->AddOption("Yes");
		testprop->AddOption("No");

		testprop->AllowEdit(false);

		testprop->SetData(ValueType::LookType);

		PropertyGrid.AddProperty(testprop);
	}

	{
		auto group = new CMFCPropertyGridProperty("Position", 0, true);
		PropertyGrid.AddProperty(group);

		{
			auto pos = new CMFCPropertyGridProperty("X", COleVariant(0.0f));
			pos->SetData(ValueType::PositionX);
			group->AddSubItem(pos);
		}

		{
			auto pos = new CMFCPropertyGridProperty("Y", COleVariant(0.0f));
			pos->SetData(ValueType::PositionY);
			group->AddSubItem(pos);
		}

		{
			auto pos = new CMFCPropertyGridProperty("Z", COleVariant(0.0f));
			pos->SetData(ValueType::PositionZ);
			group->AddSubItem(pos);
		}
	}

	{
		auto group = new CMFCPropertyGridProperty("Angle", 0, true);
		PropertyGrid.AddProperty(group);

		{
			auto pos = new CMFCPropertyGridProperty("X", COleVariant(0.0f));
			pos->SetData(ValueType::AngleX);
			group->AddSubItem(pos);
		}

		{
			auto pos = new CMFCPropertyGridProperty("Y", COleVariant(0.0f));
			pos->SetData(ValueType::AngleY);
			group->AddSubItem(pos);
		}

		{
			auto pos = new CMFCPropertyGridProperty("Z", COleVariant(0.0f));
			pos->SetData(ValueType::AngleZ);
			group->AddSubItem(pos);
		}
	}

	{
		auto testprop = new CMFCPropertyGridProperty("FOV", COleVariant(90l));
		testprop->EnableSpinControl(true, 20, 140);
		testprop->SetData(ValueType::FOV);

		PropertyGrid.AddProperty(testprop);
	}

	{
		auto testprop = new CMFCPropertyGridProperty("Speed", COleVariant(200l));
		testprop->EnableSpinControl(true, 1, 1000);
		testprop->SetData(ValueType::Speed);

		PropertyGrid.AddProperty(testprop);
	}

	/*
		The property grid is not resized automatically
		when new items are added, and the columns are too small by default.
	*/
	CRect rect;
	PropertyGrid.GetWindowRect(&rect);
	PropertyGrid.PostMessageA(WM_SIZE, 0, MAKELONG(rect.Width(), rect.Height()));

	return true;
}

void HLCamEditorDialog::OnOK()
{

}

void HLCamEditorDialog::OnCancel()
{

}

void HLCamEditorDialog::DoDataExchange(CDataExchange* exchange)
{
	__super::DoDataExchange(exchange);
	
	DDX_Control(exchange, IDC_MFCPROPERTYGRID1, PropertyGrid);
	DDX_Control(exchange, IDC_TREE1, TreeControl);
}

void HLCamEditorDialog::RebuildPropertyGrid()
{

}

void HLCamEditorDialog::OnGetMinMaxInfo(MINMAXINFO* minmaxinfo)
{
	minmaxinfo->ptMinTrackSize.x = 480;
	minmaxinfo->ptMinTrackSize.y = 394;
}

LRESULT HLCamEditorDialog::OnPropertyGridItemChanged(WPARAM controlid, LPARAM propptr)
{
	auto prop = reinterpret_cast<CMFCPropertyGridProperty*>(propptr);

	auto valuetype = static_cast<ValueType::Type>(prop->GetData());

	int a = 5;
	a = a;

	

	return 0;
}

void HLCamEditorDialog::OnClose()
{
	EndDialog(0);
}

void HLCamEditorDialog::OnContextMenu(CWnd* window, CPoint point)
{
	if (window == &TreeControl)
	{
		size_t flags;

		TreeControl.ScreenToClient(&point);

		auto test = TreeControl.HitTest(point , &flags);

		auto asd = TreeControl.GetItemText(test);

		int a = 5;
		a = a;
	}
}

void HLCamEditorDialog::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEWW treeviewitem = reinterpret_cast<LPNMTREEVIEWW>(pNMHDR);
	


	*pResult = 0;
}
