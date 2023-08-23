// AX.H
#ifndef _AX_H
#define _AX_H

// messages
#define AX_QUERYINTERFACE (WM_USER + 1)
#define AX_INPLACE (WM_USER + 2)
#define AX_GETAXINTERFACE (WM_USER + 3)
#define AX_CONNECTOBJECT (WM_USER + 4)
#define AX_DISCONNECTOBJECT (WM_USER + 5)
#define AX_SETDATAADVISE (WM_USER + 6)
#define AX_DOVERB (WM_USER + 7)
#define AX_SETCOMMANDCALLBACK  (WM_USER + 8)
#define AX_SETDISPATCHNOTIFICATION (WM_USER + 9)
#define AX_SETSERVICEPROVIDER (WM_USER + 10)
#define AX_SETDISPATCHNOTIFICATIONFUNC (WM_USER + 11)
#define AX_RECREATE (WM_USER + 12)


// notifications
#define AXN_SIZE 1


// Registration function
ATOM AXRegister();
int AXConnectObject(IUnknown* Container, REFIID riid, IUnknown* Advisor, IConnectionPointContainer** picpc, IConnectionPoint** picp);
void AXDisconnectObject(IConnectionPointContainer* icpc, IConnectionPoint* icp, unsigned int Cookie);

struct AX_CONNECTSTRUCT
{
	IUnknown* Advisor;
	IConnectionPointContainer* icpc;
	IConnectionPoint* icp;
	DWORD id;
	CLSID SpecialIIDForceOK;
};


#pragma warning(disable:4584)
// Class AXClientSide
class AXClientSite :
	public IOleClientSite,
	public IUnknown,
	public IServiceProvider,
	public IDispatch,
	public IAdviseSink,
	public IOleInPlaceSite,
	public IOleInPlaceFrame
{
protected:

	int refNum;

public:


	HWND Window;
	HWND Parent;
	HMENU Menu;
	bool InPlace;
	bool ExternalPlace;
	bool CalledCanInPlace;
	CLSID SpecialIIDForceOK;

	class AX* ax;

	// MyClientSite Methods
	AXClientSite();
	virtual ~AXClientSite();
	STDMETHODIMP_(void) OnDataChange2(FORMATETC*);

	// IUnknown methods
	STDMETHODIMP QueryInterface(REFIID iid, void**ppvObject);
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();

	// IServiceProvider methods
	STDMETHODIMP QueryService(REFGUID guid, REFIID iid, void ** ppvObject);

	// IOleClientSite methods
	STDMETHODIMP SaveObject();
	STDMETHODIMP GetMoniker(DWORD dwA, DWORD dwW, IMoniker**pm);
	STDMETHODIMP GetContainer(IOleContainer**pc);
	STDMETHODIMP ShowObject();
	STDMETHODIMP OnShowWindow(BOOL f);
	STDMETHODIMP RequestNewObjectLayout();

	// IAdviseSink methods
	STDMETHODIMP_(void) OnDataChange(FORMATETC *pFormatEtc, STGMEDIUM *pStgmed);

	STDMETHODIMP_(void) OnViewChange(DWORD dwAspect, LONG lIndex);
	STDMETHODIMP_(void) OnRename(IMoniker * pmk);
	STDMETHODIMP_(void) OnSave();
	STDMETHODIMP_(void) OnClose();

	// IOleInPlaceSite methods
	STDMETHODIMP GetWindow(HWND *p);
	STDMETHODIMP ContextSensitiveHelp(BOOL);
	STDMETHODIMP CanInPlaceActivate();
	STDMETHODIMP OnInPlaceActivate();
	STDMETHODIMP OnUIActivate();
	STDMETHODIMP GetWindowContext(IOleInPlaceFrame** ppFrame, IOleInPlaceUIWindow **ppDoc, LPRECT r1, LPRECT r2, LPOLEINPLACEFRAMEINFO o);
	STDMETHODIMP Scroll(SIZE s);
	STDMETHODIMP OnUIDeactivate(int);
	STDMETHODIMP OnInPlaceDeactivate();
	STDMETHODIMP DiscardUndoState();
	STDMETHODIMP DeactivateAndUndo();
	STDMETHODIMP OnPosRectChange(LPCRECT);

	// IOleInPlaceFrame methods
	STDMETHODIMP GetBorder(LPRECT l);
	STDMETHODIMP RequestBorderSpace(LPCBORDERWIDTHS);
	STDMETHODIMP SetBorderSpace(LPCBORDERWIDTHS w);
	STDMETHODIMP SetActiveObject(IOleInPlaceActiveObject*pV, LPCOLESTR s);
	STDMETHODIMP InsertMenus(HMENU h, LPOLEMENUGROUPWIDTHS x);
	STDMETHODIMP SetMenu(HMENU h, HOLEMENU hO, HWND hw);
	STDMETHODIMP RemoveMenus(HMENU h);
	STDMETHODIMP SetStatusText(LPCOLESTR t);
	STDMETHODIMP EnableModeless(BOOL f);
	STDMETHODIMP TranslateAccelerator(LPMSG, WORD);


	// IDispatch Methods
	HRESULT _stdcall GetTypeInfoCount(unsigned int * pctinfo);
	HRESULT _stdcall GetTypeInfo(unsigned int iTInfo, LCID lcid, ITypeInfo FAR* FAR* ppTInfo);
	HRESULT _stdcall GetIDsOfNames(REFIID riid, OLECHAR FAR* FAR*, unsigned int cNames, LCID lcid, DISPID FAR*);
	HRESULT _stdcall Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr);

	// IOleControlSite Methods
};




// Class AX
class AX
{
public:

	AX(char* clsid);
	CLSID GetCLSID();
	~AX();


	void Init(char* clsid);
	void Clean();

	AXClientSite Site;
	IID* iid;
	IOleObject* OleObject;
	IStorage* Storage;
	IViewObject* View;
	IDataObject* Data;
	IUnknown* Unk;
	IOleInPlaceActiveObject* Pao;
	IServiceProvider* CustomServiceProvider;
	AX_CONNECTSTRUCT* tcs;
	bool AddMenu;
	DWORD AdviseToken;
	DWORD DAdviseToken[100];
	HWND CommandCallbackWindow;
	HWND DispatchNotificationWindow;
	void(__stdcall *DispatchNotificationFunction)(struct AXDISPATCHNOTIFICATION*);
	UINT DispatchNotificationMessage;




private:

	CLSID clsid;


};


struct AXDISPATCHNOTIFICATION
{
	class AX* ax;
	DISPID dispIdMember;
	REFIID riid;
	LCID lcid;
	WORD wFlags;
	DISPPARAMS FAR* pDispParams;
	VARIANT FAR* pVarResult;
	EXCEPINFO FAR* pExcepInfo;
	unsigned int FAR* puArgErr;
};



#endif // _AX_H