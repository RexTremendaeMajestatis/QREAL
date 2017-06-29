/* Copyright 2007-2015 QReal Research Group
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "ifWithOneVisitedRule.h"

using namespace generatorBase::semantics;
using namespace qReal;

IfWithOneVisitedRule::IfWithOneVisitedRule(SemanticTree *tree, const Id &id
		, const LinkInfo &thenLink, const LinkInfo &elseLink)
	: IfBlockRuleBase(tree, id, thenLink, elseLink)
{
}

bool IfWithOneVisitedRule::apply()
{
	int visitedCount = 0;

	if (alreadyCreated(mThenLink)) {
		++visitedCount;
	}

	if (alreadyCreated(mElseLink)) {
		++visitedCount;
	}

	if (visitedCount != 1) {
		return false;
	}

	const LinkInfo &visitedLink = alreadyCreated(mThenLink) ? mThenLink : mElseLink;
	const LinkInfo &unvisitedLink = alreadyCreated(mThenLink) ? mElseLink : mThenLink;

	IfNode * const thisNode = static_cast<IfNode *>(mTree->findNodeFor(mId));
	SemanticNode *newNode = mTree->produceNodeFor(unvisitedLink.target);

	NonZoneNode * const nextNode = mTree->findNodeFor(visitedLink.target);
	if (nextNode->parentZone() != thisNode->parentZone()) {
		(alreadyCreated(mThenLink) ? thisNode->elseZone() : thisNode->thenZone())->appendChild(newNode);
		return false;
	}

	LoopNode * const loop = makeLoopStartingFrom(nextNode);
	loop->bodyZone()->removeChild(thisNode);
	loop->bindTo(mId);
	loop->setForm(true);
	if (alreadyCreated(mElseLink)) {
		loop->invertCondition();
	}

	loop->appendSibling(newNode);

	return true;
}