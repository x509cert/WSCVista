#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[]) {
    argc;
    argv;

	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
		return hr;

	CComPtr<IXFeedsManager> spIXFeedsManager;
	hr = spIXFeedsManager.CoCreateInstance(CLSID_XFeedsManager,NULL, CLSCTX_INPROC_SERVER);
	if (FAILED(hr))
		return hr;

	CComPtr<IXFeedFolder> spIXRoot;
	hr = spIXFeedsManager->RootFolder(IID_PPV_ARGS(&spIXRoot));
	if(SUCCEEDED(hr)) {
		CComPtr<IXFeedsEnum> spIXFeedsEnum;
		hr = spIXRoot->Feeds(&spIXFeedsEnum);
		if (SUCCEEDED(hr)) {
			UINT uiFeedCount = 0;
			hr = spIXFeedsEnum->Count(&uiFeedCount);
			while (uiFeedCount && (SUCCEEDED(hr))) {
				CComPtr<IXFeed> spIXFeed;
				hr = spIXFeedsEnum->Item(--uiFeedCount, IID_PPV_ARGS(&spIXFeed));
				if (SUCCEEDED(hr)) {
					LPWSTR wszName = NULL;
					if (SUCCEEDED(spIXFeed->Name(&wszName))) {
                  wprintf(L"%s",wszName ? wszName : L"No Name");
						CoTaskMemFree(wszName);
					}

					LPWSTR wszUrl = NULL;
					if (SUCCEEDED(spIXFeed->Url(&wszUrl))) {
						wprintf(L" from %s",wszUrl);
						CoTaskMemFree(wszUrl);
					}

					UINT cItems;
					if (SUCCEEDED(spIXFeed->ItemCount(&cItems))) {
						wprintf(L" has %d items.\n",cItems);
					}

					spIXFeed = NULL;
				}
				spIXFeedsEnum = NULL;
				if (uiFeedCount)
					hr = spIXRoot->Feeds(&spIXFeedsEnum);
			}
		}
	}

	spIXRoot = NULL;
	spIXFeedsManager = NULL;

	CoUninitialize();
}
