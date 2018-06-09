/***************************************************************************
 * Copyright 1998-2018 by authors (see AUTHORS.txt)                        *
 *                                                                         *
 *   This file is part of LuxCoreRender.                                   *
 *                                                                         *
 * Licensed under the Apache License, Version 2.0 (the "License");         *
 * you may not use this file except in compliance with the License.        *
 * You may obtain a copy of the License at                                 *
 *                                                                         *
 *     http://www.apache.org/licenses/LICENSE-2.0                          *
 *                                                                         *
 * Unless required by applicable law or agreed to in writing, software     *
 * distributed under the License is distributed on an "AS IS" BASIS,       *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.*
 * See the License for the specific language governing permissions and     *
 * limitations under the License.                                          *
 ***************************************************************************/

#include "slg/lights/strategies/dlscache.h"
#include "slg/lights/strategies/dlscacheimpl.h"
#include "slg/scene/scene.h"

using namespace std;
using namespace luxrays;
using namespace slg;

//------------------------------------------------------------------------------
// LightStrategyLogPower
//------------------------------------------------------------------------------

void LightStrategyDLSCache::Preprocess(const Scene *scn, const LightStrategyTask taskType) {
	distributionStrategy.Preprocess(scn, taskType);
	
	if (taskType == TASK_ILLUMINATE)
		DLSCache.Build(scn);
}

LightSource *LightStrategyDLSCache::SampleLights(const float u, float *pdf) const {
	return distributionStrategy.SampleLights(u, pdf);
}

float LightStrategyDLSCache::SampleLightPdf(const LightSource *light, const luxrays::Point &rayOrig) const {
	return distributionStrategy.SampleLightPdf(light, rayOrig);
}

Properties LightStrategyDLSCache::ToProperties() const {
	return Properties() <<
			Property("lightstrategy.type")(LightStrategyType2String(GetType()));
}

// Static methods used by LightStrategyRegistry

Properties LightStrategyDLSCache::ToProperties(const Properties &cfg) {
	return Properties() <<
			cfg.Get(GetDefaultProps().Get("lightstrategy.type"));
}

LightStrategy *LightStrategyDLSCache::FromProperties(const Properties &cfg) {
	return new LightStrategyDLSCache();
}

const Properties &LightStrategyDLSCache::GetDefaultProps() {
	static Properties props = Properties() <<
			LightStrategy::GetDefaultProps() <<
			Property("lightstrategy.type")(GetObjectTag());

	return props;
}