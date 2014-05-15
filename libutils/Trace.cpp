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

#include <utils/misc.h>
#include <utils/Trace.h>

// Engle, add for MTK, start
#if defined(TARGET_JB_TRACER)
#define LOG_TAG "Trace"
#include <cutils/properties.h>
#include <utils/Log.h>
#endif
// Engle, add for MTK, end

static void traceInit() __attribute__((constructor));

static void traceInit()
{
    ::android::add_sysprop_change_callback(atrace_update_tags, 0);
}

// Engle, add for MTK, start
#if defined(TARGET_JB_TRACER)

namespace android {

	volatile int32_t Tracer::sIsReady = 0;
	int Tracer::sTraceFD = -1;
	uint64_t Tracer::sEnabledTags = 0;
	Mutex Tracer::sMutex;

	void Tracer::changeCallback() {
	}

	void Tracer::init() {
	}

	void Tracer::loadSystemProperty() {
	}
} // namespace andoid
#endif
// Engle, add for MTK, end