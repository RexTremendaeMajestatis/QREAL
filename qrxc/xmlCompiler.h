/* Copyright 2007-2016 QReal Research Group
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

#pragma once

#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QDir>

class Type;
class Editor;
class Diagram;
class GraphicType;

namespace utils {
	class OutFile;
}

class XmlCompiler
{
public:
	XmlCompiler();
	~XmlCompiler();

	QString pluginName() const;
	bool compile(const QString &inputXmlFileName, const QString &sourcesRootFolder);
	Editor *loadXmlFile(const QDir &currentDir, const QString &inputXmlFileName);
	Diagram *getDiagram(const QString &diagramName);
	void addResource(const QString &resourceName);

private:
	void generateCode();
	void generateElementClasses();
	void generatePluginHeader();
	void generatePluginSource();
	void generateAutogeneratedDisclaimer(utils::OutFile &out);
	void generateIncludes(utils::OutFile &out);
	void generateInitPlugin(utils::OutFile &out);
	void generateInitMultigraph(utils::OutFile &out);
	void generateLinks(utils::OutFile &out, const Type *from, const QStringList &to
			, const QString &linkType, bool areNamesNormalized);
	void generateNameMappings(utils::OutFile &out);
	void generateNodesAndEdgesSets(utils::OutFile &out);
	void generateExplosionsMappings(utils::OutFile &out, const GraphicType *graphicType);
	void generateReferenceProperties(utils::OutFile &out);
	void generatePossibleEdges(utils::OutFile &out);
	void generateNodesAndEdges(utils::OutFile &out);
	void generateEnumValues(utils::OutFile &out);
	void generateResourceFile();
	void generatePaletteGroupsLists(utils::OutFile &out);
	void generatePaletteGroupsDescriptions(utils::OutFile &out);
	void generateShallPaletteBeSorted(utils::OutFile &out);

	QMap<QString, Editor *> mEditors;
	QString mPluginName;
	QString mPluginVersion;
	QString mResources;
	QString mCurrentEditor;
	QString mSourcesRootFolder;
};