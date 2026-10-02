#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class DocumentElement
{ // abstraction
public:
    virtual string render() = 0;
};

class TextElement : public DocumentElement
{
private:
    string text;

public:
    TextElement(string text)
    {
        this->text = text;
    }
    string render() override
    {
        return text;
    }
};
class ImageElement : public DocumentElement
{
private:
    string imagePath;

public:
    ImageElement(string imagePath)
    {
        this->imagePath = imagePath;
    }
    string render() override
    {
        return "[Image:" + imagePath + "]";
    }
};
class NewLineElement : public DocumentElement
{

public:
    string render() override
    {
        return "\n";
    }
};
class TabSpaceElement : public DocumentElement
{

public:
    string render() override
    {
        return "\t";
    }
};

class Document
{
private:
    vector<DocumentElement *> docElements;

public:
    void addElement(DocumentElement *element)
    {
        docElements.push_back(element);
    }
    string render()
    {
        string result;
        for (auto element : docElements)
        {
            result += element->render();
        }
        return result;
    }
};

// persistance abstraction
class DocumentPersistence
{
public:
    virtual void save(string data) = 0;
};

class FileStorage : public DocumentPersistence
{
public:
    void save(string data) override
    {
        ofstream outFile("doc.txt"); // creates doc.txt file
        if (outFile)
        {
            outFile << data;
            outFile.close();
            cout << "Document saved to document.txt" << endl;
        }
        else
        {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }
};

class DBStorage : public DocumentPersistence
{
public:
    void save(string data) override
    {
        // Simulating database storage
    }
};

// managing client interactions
class DocumentEditor
{
private:
    Document *document;
    DocumentPersistence *storage;
    string renderedDocument;

public:
    DocumentEditor(Document *document, DocumentPersistence *storage)
    {
        this->document = document;
        this->storage = storage;
    }
    void addText(string text)
    {
        document->addElement(new TextElement(text));
    }
    void addImage(string imagePath)
    {
        document->addElement(new ImageElement(imagePath));
    }
    void addNewLine()
    {
        document->addElement(new NewLineElement());
    }
    void addTabSpace()
    {
        document->addElement(new TabSpaceElement());
    }
    string renderDocument()
    {
        if (renderedDocument.empty())
        {
            renderedDocument = document->render();
        }
        return renderedDocument;
    }
    void saveDocument()
    {
        storage->save(renderDocument());
    }
};
int main()
{
    Document *document = new Document();
    DocumentPersistence *storage = new FileStorage();
    DocumentEditor *editor = new DocumentEditor(document, storage);
    editor->addText("Hello, world!");
    editor->addNewLine();
    editor->addText("This is a real-world doc editor LLD example.");
    editor->addNewLine();
    editor->addTabSpace();
    editor->addText("Indented text after a tab space.");
    editor->addNewLine();
    editor->addImage("image.jpg");

    cout << editor->renderDocument() << endl;
    editor->saveDocument();
    return 0;
}