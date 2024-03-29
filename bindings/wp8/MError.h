#pragma once

#include "megaapi.h"

namespace mega
{
	using namespace Windows::Foundation;
	using Platform::String;

	public enum class MErrorType
	{
		API_OK = 0,
		API_EINTERNAL = -1,		// internal error
		API_EARGS = -2,			// bad arguments
		API_EAGAIN = -3,		// request failed, retry with exponential backoff
		API_ERATELIMIT = -4,	// too many requests, slow down
		API_EFAILED = -5,		// request failed permanently
		API_ETOOMANY = -6,		// too many requests for this resource
		API_ERANGE = -7,		// resource access out of rage
		API_EEXPIRED = -8,		// resource expired
		API_ENOENT = -9,		// resource does not exist
		API_ECIRCULAR = -10,	// circular linkage
		API_EACCESS = -11,		// access denied
		API_EEXIST = -12,		// resource already exists
		API_EINCOMPLETE = -13,	// request incomplete
		API_EKEY = -14,			// cryptographic error
		API_ESID = -15,			// bad session ID
		API_EBLOCKED = -16,		// resource administratively blocked
		API_EOVERQUOTA = -17,	// quote exceeded
		API_ETEMPUNAVAIL = -18,	// resource temporarily not available
		API_ETOOMANYCONNECTIONS = -19, // too many connections on this resource
		API_EWRITE = -20,		// file could not be written to
		API_EREAD = -21,		// file could not be read from
		API_EAPPKEY = -22		// invalid or missing application key
	};

	public ref class MError sealed
	{
		friend ref class MegaSDK;
		friend class DelegateMRequestListener;
		friend class DelegateMTransferListener;
		friend class DelegateMListener;

	public:
		virtual ~MError();
		MError^ copy();
		MErrorType getErrorCode();
		String^ getErrorString();
		String^ toString();
		int getNextAttempt();
		static String^ getErrorString(int errorCode);

	private:
		MError(MegaError *megaError, bool cMemoryOwn);
		MegaError *megaError;
		MegaError *getCPtr();
		bool cMemoryOwn;
	};
}
