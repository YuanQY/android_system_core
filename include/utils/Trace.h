/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_TRACE_H
#define ANDROID_TRACE_H

#ifdef HAVE_ANDROID_OS

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <cutils/compiler.h>
#include <utils/threads.h>
#include <cutils/trace.h>

// See <cutils/trace.h> for more ATRACE_* macros.

// ATRACE_NAME traces the beginning and end of the current scope.  To trace
// the correct start and end times this macro should be declared first in the
// scope body.
#define ATRACE_NAME(name) android::ScopedTrace ___tracer(ATRACE_TAG, name)
// ATRACE_CALL is an ATRACE_NAME that uses the current function name.
#define ATRACE_CALL() ATRACE_NAME(__FUNCTION__)

namespace android {

// Engle, add for MTK, start
#if defined(TARGET_JB_TRACER)
class Tracer {
	public:

	static uint64_t getEnabledTags() {
		initIfNeeded();
		return sEnabledTags;
	}

	static inline bool isTagEnabled(uint64_t tag) {
		initIfNeeded();
		return sEnabledTags & tag;
	}

	static inline void traceCounter(uint64_t tag, const char* name,
											int32_t value) {

	}

	static inline void traceBegin(uint64_t tag, const char* name) {

	}

	static inline void traceEnd(uint64_t tag) {

	}

	private:

	static inline void initIfNeeded() {

	}
	static void changeCallback();

	// init opens the trace marker file for writing and reads the
	// atrace.tags.enableflags system property. It does this only the first
	// time it is run, using sMutex for synchronization.
	static void init();

	// retrieve the current value of the system property.
	static void loadSystemProperty();

	// sIsReady is a boolean value indicating whether a call to init() has
	// completed in this process. It is initialized to 0 and set to 1 when the
	// first init() call completes. It is set to 1 even if a failure occurred
	// in init (e.g. the trace marker file couldn't be opened).
	//
	// This should be checked by all tracing functions using an atomic acquire
	// load operation before calling init(). This check avoids the need to lock
	// a mutex each time a trace function gets called.
	static volatile int32_t sIsReady;

	// sTraceFD is the file descriptor used to write to the kernel's trace
	// buffer. It is initialized to -1 and set to an open file descriptor in
	// init() while a lock on sMutex is held.
	//
	// This should only be used by a trace function after init() has
	// successfully completed.
	static int sTraceFD;

	// sEnabledTags is the set of tag bits for which tracing is currently
	// enabled. It is initialized to 0 and set based on the
	// atrace.tags.enableflags system property in init() while a lock on sMutex
	// is held.
	//
	// This should only be used by a trace function after init() has
	// successfully completed.
	//
	// This value is only ever non-zero when tracing is initialized and sTraceFD is not -1.
	static uint64_t sEnabledTags;

	// sMutex is used to protect the execution of init().
	static Mutex sMutex;
};
#endif
// Engle, add for MTK, end

class ScopedTrace {
public:
inline ScopedTrace(uint64_t tag, const char* name)
    : mTag(tag) {
    atrace_begin(mTag,name);
}

inline ~ScopedTrace() {
    atrace_end(mTag);
}

private:
    uint64_t mTag;
};

}; // namespace android

#else // HAVE_ANDROID_OS

#define ATRACE_NAME(...)
#define ATRACE_CALL()

#endif // HAVE_ANDROID_OS

#endif // ANDROID_TRACE_H
