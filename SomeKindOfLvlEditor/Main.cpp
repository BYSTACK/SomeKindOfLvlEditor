#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <vector>
#include <SFML/Graphics.hpp>
#include "gameObject.h"
#include <fstream>

using namespace std;
using namespace sf;

bool wallTC = false;
bool itemTC = false;
bool cannonTC = false;
bool spikeTC = false;
bool gravityTC = false;
bool decorationTC = false;
bool buttonPressed = false;
bool openButtonPressed = false;
bool backChanged = false;
bool lWasPressed = false;
bool rWasPressed = false;

int grChangerNum = 5;
int wallNum = 16;
int spikeNum = 2;
int cannonNum = 4;
int itemNum = 2;
int decorationNum = 1;


void decorationTextChanged()
{
	decorationTC = true;
}

void wallTextChanged()
{
	wallTC = true;
}

void bgChanged()
{
	backChanged = true;
}

void itemTextChanged()
{
	itemTC = true;
}

void cannonTextChanged()
{
	cannonTC = true;
}

void spikeTextChanged()
{
	spikeTC = true;
}

void gravityTextChanged()
{
	gravityTC = true;
}

void exportPressed()
{
	buttonPressed = true;
}

void openPressed()
{
	openButtonPressed = true;
}

int main()
{
	ifstream ist("Resources/rdata.rdf");

	ist >> grChangerNum;

	ist >> cannonNum;
	ist >> grChangerNum;
	ist >> itemNum;
	ist >> spikeNum;
	ist >> wallNum;
	ist >> decorationNum;
	
	ist.close();

	sf::RenderWindow app_window(sf::VideoMode(1100, 900), "SomeKindOfLvlEditor", sf::Style::Default);

	app_window.resetGLStates();
	sfg::SFGUI sfgui;

	auto window = sfg::Window::Create();

	window->SetTitle("Settings");
	window->SetPosition(sf::Vector2f(780.f, 0.f));

	auto optionsBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	optionsBox->SetSpacing(5.f);

	auto roomNameBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);

	auto roomNameEntry = sfg::Entry::Create("r1");
	roomNameEntry->SetRequisition(sf::Vector2f(40.f, 0.f));

	auto roomIdEntry = sfg::Entry::Create("0");
	roomIdEntry->SetRequisition(sf::Vector2f(40.f, 0.f));

	auto backIdEntry = sfg::Entry::Create("0");
	backIdEntry->SetRequisition(sf::Vector2f(40.f, 0.f));
	backIdEntry->GetSignal(sfg::Entry::OnKeyRelease).Connect(bgChanged);

	auto roomLightLevelEntry = sfg::Entry::Create("2");
	roomLightLevelEntry->SetRequisition(sf::Vector2f(40.f, 0.f));

	auto roomNameLabel = sfg::Label::Create();
	auto roomIdLabel = sfg::Label::Create();
	auto backIdLabel = sfg::Label::Create();
	auto roomLightLevelLabel = sfg::Label::Create();

	roomNameLabel->SetText("Room name");
	roomIdLabel->SetText("ID");
	backIdLabel->SetText("bg");
	roomLightLevelLabel->SetText("light");

	roomNameBox->Pack(roomNameLabel);
	roomNameBox->Pack(roomNameEntry);

	roomNameBox->Pack(roomIdLabel);
	roomNameBox->Pack(roomIdEntry);

	roomNameBox->Pack(backIdLabel);
	roomNameBox->Pack(backIdEntry);

	roomNameBox->Pack(roomLightLevelLabel);
	roomNameBox->Pack(roomLightLevelEntry);

	roomNameBox->SetSpacing(2.f);

	optionsBox->Pack(roomNameBox);

	auto rRoomBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
	auto rRoomEntry = sfg::Entry::Create("NoRoom");
	rRoomEntry->SetRequisition(sf::Vector2f(80.f, 0.f));
	auto rRoomLabel = sfg::Label::Create();

	rRoomLabel->SetText("On right");

	rRoomBox->Pack(rRoomLabel);
	rRoomBox->Pack(rRoomEntry);

	optionsBox->Pack(rRoomBox);

	auto lRoomBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
	auto lRoomEntry = sfg::Entry::Create("NoRoom");
	lRoomEntry->SetRequisition(sf::Vector2f(80.f, 0.f));
	auto lRoomLabel = sfg::Label::Create();

	lRoomLabel->SetText("On left");

	lRoomBox->Pack(lRoomLabel);
	lRoomBox->Pack(lRoomEntry);

	optionsBox->Pack(lRoomBox);

	auto aRoomBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
	auto aRoomEntry = sfg::Entry::Create("NoRoom");
	aRoomEntry->SetRequisition(sf::Vector2f(80.f, 0.f));
	auto aRoomLabel = sfg::Label::Create();

	aRoomLabel->SetText("Above");

	aRoomBox->Pack(aRoomLabel);
	aRoomBox->Pack(aRoomEntry);

	optionsBox->Pack(aRoomBox);

	auto bRoomBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
	auto bRoomEntry = sfg::Entry::Create("NoRoom");
	bRoomEntry->SetRequisition(sf::Vector2f(80.f, 0.f));
	auto bRoomLabel = sfg::Label::Create();

	bRoomLabel->SetText("Below");

	bRoomBox->Pack(bRoomLabel);
	bRoomBox->Pack(bRoomEntry);

	optionsBox->Pack(bRoomBox);



	auto wallSetupBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
	auto itemSetupBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
	auto spikeSetupBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
	auto cannonSetupBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
	auto gravitySetupBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
	auto decorationSetupBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);

	auto wallPicBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
	auto itemPicBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
	auto spikePicBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
	auto cannonPicBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
	auto gravityPicBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
	auto decorationPicBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);

	auto radioWall = sfg::RadioButton::Create("Wall");
	auto radioItem = sfg::RadioButton::Create("Item", radioWall->GetGroup());
	auto radioSpike = sfg::RadioButton::Create("Spike", radioWall->GetGroup());
	auto radioCannon = sfg::RadioButton::Create("Cannon", radioWall->GetGroup());
	auto radioGravity = sfg::RadioButton::Create("GrChanger", radioWall->GetGroup());
	auto radioDecoration = sfg::RadioButton::Create("Decoration", radioWall->GetGroup());

	radioWall->SetActive(true);

	auto wallTexture = sfg::SpinButton::Create(0, wallNum-1, 1);
	wallTexture->GetSignal(sfg::SpinButton::OnValueChanged).Connect(wallTextChanged);
	wallTexture->SetRequisition(sf::Vector2f(30.f, 0.f));
	wallTexture->SetDigits(0);

	auto itemTexture = sfg::SpinButton::Create(0, itemNum-1, 1);
	itemTexture->GetSignal(sfg::SpinButton::OnValueChanged).Connect(itemTextChanged);
	itemTexture->SetRequisition(sf::Vector2f(30.f, 0.f));
	itemTexture->SetDigits(0);

	auto spikeTexture = sfg::SpinButton::Create(0, spikeNum-1, 1);
	spikeTexture->GetSignal(sfg::SpinButton::OnValueChanged).Connect(spikeTextChanged);
	spikeTexture->SetRequisition(sf::Vector2f(30.f, 0.f));
	spikeTexture->SetDigits(0);

	auto cannonTexture = sfg::SpinButton::Create(0, cannonNum-1, 1);
	cannonTexture->GetSignal(sfg::SpinButton::OnValueChanged).Connect(cannonTextChanged);
	cannonTexture->SetRequisition(sf::Vector2f(30.f, 0.f));
	cannonTexture->SetDigits(0);

	auto gravityTexture = sfg::SpinButton::Create(0, grChangerNum-1, 1);
	gravityTexture->GetSignal(sfg::SpinButton::OnValueChanged).Connect(gravityTextChanged);
	gravityTexture->SetRequisition(sf::Vector2f(30.f, 0.f));
	gravityTexture->SetDigits(0);

	auto decorationTexture = sfg::SpinButton::Create(0, decorationNum - 1, 1);
	decorationTexture->GetSignal(sfg::SpinButton::OnValueChanged).Connect(decorationTextChanged);
	decorationTexture->SetRequisition(sf::Vector2f(30.f, 0.f));
	decorationTexture->SetDigits(0);

	auto decorationLayer = sfg::SpinButton::Create(0, 1, 1);
	decorationLayer->SetRequisition(sf::Vector2f(30.f, 0.f));
	decorationLayer->SetDigits(0);

	auto delayLabel = sfg::Label::Create("Shot delay");
	auto offsetLabel = sfg::Label::Create("First shot delay");

	auto lightLevelLabel = sfg::Label::Create("Light level");

	auto applyButton = sfg::Button::Create("Apply");

	auto lightLevel = sfg::SpinButton::Create(0, 100, 1);
	lightLevel->SetRequisition(sf::Vector2f(30.f, 0.f));
	lightLevel->SetDigits(0);

	auto cannonDelay = sfg::SpinButton::Create(1, 10000, 1);
	cannonDelay->SetRequisition(sf::Vector2f(30.f, 0.f));
	cannonDelay->SetDigits(0);

	auto cannonOffset = sfg::SpinButton::Create(0, 50000, 1);
	cannonOffset->SetRequisition(sf::Vector2f(30.f, 0.f));
	cannonOffset->SetDigits(0);

	wallSetupBox->Pack(radioWall);
	itemSetupBox->Pack(radioItem);
	cannonSetupBox->Pack(radioCannon);
	spikeSetupBox->Pack(radioSpike);
	gravitySetupBox->Pack(radioGravity);
	decorationSetupBox->Pack(radioDecoration);

	wallSetupBox->Pack(wallTexture);
	itemSetupBox->Pack(itemTexture);
	cannonSetupBox->Pack(cannonTexture);
	spikeSetupBox->Pack(spikeTexture);
	gravitySetupBox->Pack(gravityTexture);
	decorationSetupBox->Pack(decorationTexture);
	
	optionsBox->Pack(wallSetupBox);
	optionsBox->Pack(itemSetupBox);
	optionsBox->Pack(spikeSetupBox);
	optionsBox->Pack(cannonSetupBox);

	optionsBox->Pack(delayLabel);
	optionsBox->Pack(cannonDelay);
	optionsBox->Pack(offsetLabel);
	optionsBox->Pack(cannonOffset);
	optionsBox->Pack(gravitySetupBox);
	optionsBox->Pack(decorationSetupBox);
	optionsBox->Pack(lightLevelLabel);
	optionsBox->Pack(lightLevel);
	optionsBox->Pack(applyButton);

	wallSetupBox->Pack(wallPicBox);
	itemSetupBox->Pack(itemPicBox);
	cannonSetupBox->Pack(cannonPicBox);
	spikeSetupBox->Pack(spikePicBox);
	gravitySetupBox->Pack(gravityPicBox);
	decorationSetupBox->Pack(decorationPicBox);
	decorationSetupBox->Pack(decorationLayer);

	auto exportButton = sfg::Button::Create();
	exportButton->SetLabel("Save");
	exportButton->GetSignal(sfg::Button::OnMouseLeftPress).Connect(exportPressed);

	optionsBox->Pack(exportButton);

	auto fileNameEntry = sfg::Entry::Create();
	fileNameEntry->SetRequisition(sf::Vector2f(80.f, 0.f));

	auto openButton = sfg::Button::Create();
	openButton->SetLabel("Open");
	openButton->GetSignal(sfg::Button::OnMouseLeftPress).Connect(openPressed);
	
	optionsBox->Pack(fileNameEntry);
	optionsBox->Pack(openButton);
	

	window->Add(optionsBox);

	vector<Texture*> wallTexturesT;
	vector<Texture*> itemTexturesT;
	vector<Texture*> cannonTexturesT;
	vector<Texture*> spikeTexturesT;
	vector<Texture*> gravityTexturesT;
	vector<Texture*> decorationTexturesT;

	vector<sfg::Image::Ptr> wallTexturesI;
	vector<sfg::Image::Ptr> itemTexturesI;
	vector<sfg::Image::Ptr> cannonTexturesI;
	vector<sfg::Image::Ptr> spikeTexturesI;
	vector<sfg::Image::Ptr> gravityTexturesI;
	vector<sfg::Image::Ptr> decorationTexturesI;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundImage;
	backgroundTexture.setRepeated(true);
	backgroundImage.setTextureRect(sf::IntRect(Vector2i(0, 0), Vector2i(780, 600)));

	for (int i = 0; i < wallNum; i++)
	{
		Texture* text1 = new Texture();
		Image text;
		text.loadFromFile("Resources/Walls/Wall" + to_string(i) + ".png");
		text1->loadFromFile("Resources/Walls/Wall" + to_string(i) + ".png");
		wallTexturesT.push_back(text1);
		wallTexturesI.push_back(sfg::Image::Create(text));
	}

	for (int i = 0; i < itemNum; i++)
	{
		Texture* text1 = new Texture();
		Image text;

		text.loadFromFile("Resources/Items/Item" + to_string(i) + ".png");
		text1->loadFromFile("Resources/Items/Item" + to_string(i) + ".png");

		itemTexturesT.push_back(text1);
		itemTexturesI.push_back(sfg::Image::Create(text));
	}

	for (int i = 0; i < spikeNum; i++)
	{
		Texture* text1 = new Texture();
		Image text;

		text.loadFromFile("Resources/Spikes/Spike" + to_string(i) + ".png");
		text1->loadFromFile("Resources/Spikes/Spike" + to_string(i) + ".png");

		spikeTexturesT.push_back(text1);
		spikeTexturesI.push_back(sfg::Image::Create(text));
	}

	for (int i = 0; i < cannonNum; i++)
	{
		Texture* text1 = new Texture();
		Image text;
		text.loadFromFile("Resources/Cannons/Cannon" + to_string(i) + ".png");
		text1->loadFromFile("Resources/Cannons/Cannon" + to_string(i) + ".png");

		cannonTexturesT.push_back(text1);
		cannonTexturesI.push_back(sfg::Image::Create(text));
	}

	for (int i = 0; i < grChangerNum; i++)
	{
		Texture* text1 = new Texture();
		Image text;
		text.loadFromFile("Resources/gravityChangers/gravityChanger" + to_string(i) + ".png");
		text1->loadFromFile("Resources/gravityChangers/gravityChanger" + to_string(i) + ".png");

		gravityTexturesT.push_back(text1);
		gravityTexturesI.push_back(sfg::Image::Create(text));
	}

	for (int i = 0; i < decorationNum; i++)
	{
		Texture* text1 = new Texture();
		Image text;
		text.loadFromFile("Resources/Decorations/Decoration" + to_string(i) + ".png");
		text1->loadFromFile("Resources/Decorations/Decoration" + to_string(i) + ".png");

		decorationTexturesT.push_back(text1);
		decorationTexturesI.push_back(sfg::Image::Create(text));
	}

	vector<gameObject*> objects;

	// Start the game loop
	while (app_window.isOpen()) {
		// Process events
		sf::Event event;

		
		while (app_window.pollEvent(event)) {
			// Handle events
			window->HandleEvent(event);

			// Close window : exit
			if (event.type == sf::Event::Closed) {
				return EXIT_SUCCESS;
			}

			if (event.type == Event::MouseButtonReleased)
			{
				if (lWasPressed && Mouse::getPosition(app_window).x<780.f && Mouse::getPosition(app_window).x>0.f  && Mouse::getPosition(app_window).y<600.f && Mouse::getPosition(app_window).y>0.f)
				{
					lWasPressed = false;

					gameObject* obj = new gameObject();
					if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
					{
						int x = Mouse::getPosition(app_window).x - Mouse::getPosition(app_window).x % 30;
						int y = Mouse::getPosition(app_window).y - Mouse::getPosition(app_window).y % 30;
						obj->SetPos(x, y);

						for (int i = objects.size() - 1; i >= 0; i--)
						{
							if (objects[i]->GetX() == x && objects[i]->GetY() == y)
							{
								delete objects[i];
								objects.erase(objects.begin() + i);
							}
						}
					}
					else
					{
						obj->SetPos(Mouse::getPosition(app_window).x, Mouse::getPosition(app_window).y);
					}
					objects.push_back(obj);

					if (radioWall->IsActive())
					{

						obj->SetType("Wall");
						obj->SetId((int)wallTexture->GetValue());
						obj->SetTexture(wallTexturesT[(int)wallTexture->GetValue()]);
					}
					else if (radioItem->IsActive())
					{
						obj->SetType("Item");
						obj->SetId((int)itemTexture->GetValue());
						obj->SetTexture(itemTexturesT[(int)itemTexture->GetValue()]);
					}
					else if (radioSpike->IsActive())
					{
						obj->SetType("Spike");
						obj->SetId((int)spikeTexture->GetValue());
						obj->SetTexture(spikeTexturesT[(int)spikeTexture->GetValue()]);
					}
					else if (radioCannon->IsActive())
					{
						obj->SetType("Cannon");
						obj->SetShootDelay((int)cannonDelay->GetValue());
						obj->SetShootOffset((int)cannonOffset->GetValue());
						obj->SetDir((int)cannonTexture->GetValue()%4);
						obj->SetId((int)cannonTexture->GetValue());
						obj->SetTexture(cannonTexturesT[(int)cannonTexture->GetValue()]);
					}
					else if (radioGravity->IsActive())
					{
						obj->SetType("gravityChanger");
						obj->SetDir((int)gravityTexture->GetValue()%5);
						obj->SetId((int)gravityTexture->GetValue());
						obj->SetTexture(gravityTexturesT[(int)gravityTexture->GetValue()]);
					}
					else if (radioDecoration->IsActive())
					{
						obj->SetType("Decoration");
						obj->SetId((int)decorationTexture->GetValue());
						obj->SetLightLevel((int)lightLevel->GetValue());
						obj->SetLayer((int)decorationLayer->GetValue());
						obj->SetTexture(decorationTexturesT[(int)decorationTexture->GetValue()]);
					}
				}
				if (rWasPressed && Mouse::getPosition(app_window).x<780.f && Mouse::getPosition(app_window).x>0.f  && Mouse::getPosition(app_window).y<600.f && Mouse::getPosition(app_window).y>0.f)
				{
					rWasPressed = false;
					int x = Mouse::getPosition(app_window).x;
					int y = Mouse::getPosition(app_window).y;
					for (int i = objects.size() - 1; i >= 0; i--)
					{
						if (objects[i]->GetX() < x && objects[i]->GetY() < y && objects[i]->GetX() + objects[i]->GetSizeX() > x && objects[i]->GetY() + objects[i]->GetSizeY() > y)
						{
							delete objects[i];
							objects.erase(objects.begin() + i);
							if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
							{
								break;
							}
						}
					}
				}
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (objects.size() > 0) {
					if (Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
					{
						objects[objects.size() - 1]->SetPos(objects[objects.size() - 1]->GetX(), objects[objects.size() - 1]->GetY() - 1);
					}
					if (Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
					{
						objects[objects.size() - 1]->SetPos(objects[objects.size() - 1]->GetX() - 1, objects[objects.size() - 1]->GetY());
					}
					if (Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
					{
						objects[objects.size() - 1]->SetPos(objects[objects.size() - 1]->GetX() + 1, objects[objects.size() - 1]->GetY());

					}
					if (Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
					{
						objects[objects.size() - 1]->SetPos(objects[objects.size() - 1]->GetX(), objects[objects.size() - 1]->GetY() + 1);
					}
				}
			}
		}

		if (wallTC)
		{
			wallTC = false;
			wallPicBox->RemoveAll();
			wallPicBox->PackStart(wallTexturesI[static_cast<int>(wallTexture->GetValue())]);
		}
		if (itemTC)
		{
			itemTC = false;
			itemPicBox->RemoveAll();
			itemPicBox->Pack(itemTexturesI[static_cast<int>(itemTexture->GetValue())]);
		}
		if (cannonTC)
		{
			cannonTC = false;
			cannonPicBox->RemoveAll();
			cannonPicBox->Pack(cannonTexturesI[static_cast<int>(cannonTexture->GetValue())]);
		}
		if (spikeTC)
		{
			spikeTC = false;
			spikePicBox->RemoveAll();
			spikePicBox->Pack(spikeTexturesI[static_cast<int>(spikeTexture->GetValue())]);
		}
		if (gravityTC)
		{
			gravityTC = false;
			gravityPicBox->RemoveAll();
			gravityPicBox->Pack(gravityTexturesI[static_cast<int>(gravityTexture->GetValue())]);
		}
		if (backChanged)
		{
			backChanged = false;
			backgroundTexture.loadFromFile("Resources/Backgrounds/Background"+ backIdEntry->GetText().toAnsiString() +".png");
			backgroundImage.setTexture(backgroundTexture);
		}
		if (decorationTC)
		{
			decorationTC = false;
			decorationPicBox->RemoveAll();
			decorationPicBox->Pack(decorationTexturesI[static_cast<int>(decorationTexture->GetValue())]);
		}
		if (openButtonPressed)
		{
			openButtonPressed = false;

			roomIdEntry->SetText(fileNameEntry->GetText());

			for (int i = 0; i < objects.size(); i++)
			{
				delete objects[i];
			}
			objects.clear();

			ifstream fin(fileNameEntry->GetText().toAnsiString() + ".rdf");

			std::string str, name;
			std::string rooms[4];


			float sizex, sizey;
			int back, light;

			fin >> sizex;
			fin >> sizey;
			fin >> name;
			fin >> back;
			fin >> light;

			roomNameEntry->SetText(name);
			roomLightLevelEntry->SetText(to_string(light));
			backIdEntry->SetText(to_string(back));

			bgChanged();

			for (int k = 0; k < 4; k++)
			{
				fin >> rooms[k];
			}

			rRoomEntry->SetText(rooms[0]);
			aRoomEntry->SetText(rooms[1]);
			lRoomEntry->SetText(rooms[2]);
			bRoomEntry->SetText(rooms[3]);

			fin >> str;
			while (fin) {

				if (str == "Wall")
				{
					float posx, posy;
					int textId ,useless;

					fin >> posx;
					fin >> posy;
					fin >> textId;

					for (int i = 0; i < 8; i++)
					{
						fin >> useless;
					}

					gameObject* obj = new gameObject();
					obj->SetPos(posx, posy);

					objects.push_back(obj);

					obj->SetType("Wall");
					obj->SetId(textId);
					obj->SetTexture(wallTexturesT[textId]);
				}
				else if (str == "Item")
				{
					float posx, posy;
					int textId;

					fin >> posx;
					fin >> posy;
					fin >> textId;

					gameObject* obj = new gameObject();
					obj->SetPos(posx, posy);

					objects.push_back(obj);

					obj->SetType("Item");
					obj->SetId(textId);
					obj->SetTexture(itemTexturesT[textId]);
				}
				else if (str == "Spike")
				{
					float posx, posy;
					int textId;

					fin >> posx;
					fin >> posy;
					fin >> textId;

					gameObject* obj = new gameObject();
					obj->SetPos(posx, posy);

					objects.push_back(obj);

					obj->SetType("Spike");
					obj->SetId(textId);
					obj->SetTexture(spikeTexturesT[textId]);
				}
				else if (str == "Cannon")
				{
					float posx, posy;
					int textId, dir, delay, offset;

					fin >> posx;
					fin >> posy;
					fin >> dir;
					fin >> textId;
					fin >> delay;
					fin >> offset;

					gameObject* obj = new gameObject();
					obj->SetPos(posx, posy);

					objects.push_back(obj);

					obj->SetType("Cannon");
					obj->SetId(textId);
					obj->SetTexture(cannonTexturesT[textId]);

					obj->SetShootDelay(delay);
					obj->SetShootOffset(offset);
				}
				else if (str == "gravityChanger")
				{
					float posx, posy;
					int textId, dir;

					fin >> posx;
					fin >> posy;
					fin >> dir;
					fin >> textId;

					gameObject* obj = new gameObject();
					obj->SetPos(posx, posy);

					objects.push_back(obj);

					obj->SetType("gravityChanger");
					obj->SetId(textId);
					obj->SetDir(dir);
					obj->SetTexture(gravityTexturesT[textId]);
				}
				else if (str == "Decoration")
				{
					float posx, posy;
					int textId, dir, lightLevel, layer;

					fin >> posx;
					fin >> posy;
					fin >> textId;
					fin >> lightLevel;
					fin >> layer;

					gameObject* obj = new gameObject();
					obj->SetPos(posx, posy);

					objects.push_back(obj);

					obj->SetLayer(layer);
					obj->SetLightLevel(lightLevel);
					obj->SetType("Decoration");
					obj->SetId(textId);
					obj->SetTexture(decorationTexturesT[textId]);
				}
				fin >> str;
			}

			fin.close();
		}
		if (buttonPressed)
		{
			buttonPressed = false;
			ofstream fout(roomIdEntry->GetText().toAnsiString() + ".rdf");
			fout << "780 600 " << roomNameEntry->GetText().toAnsiString() << " " << backIdEntry->GetText().toAnsiString() << " " << roomLightLevelEntry->GetText().toAnsiString() <<endl;
			fout << rRoomEntry->GetText().toAnsiString() << " " << aRoomEntry->GetText().toAnsiString() << " " << lRoomEntry->GetText().toAnsiString() << " " << bRoomEntry->GetText().toAnsiString() << endl;
			for (int i = 0; i < objects.size(); i++)
			{
				fout << objects[i]->Parse() << " ";
				if (objects[i]->GetType() == "Wall")
				{
					bool sides[8];
					for (int j = 0; j < 8; j++)
					{
						sides[j] = false;
					}
					for (int j = 0; j < objects.size(); j++)
					{
						if (objects[j]->GetType() == "Wall")
						{
							if (objects[j]->GetX() - objects[i]->GetX() == 30 && objects[j]->GetY() == objects[i]->GetY())
							{
								sides[0] = true;
							}
							else if (objects[j]->GetX() - objects[i]->GetX() == 30 && objects[i]->GetY() - objects[j]->GetY() == 30)
							{
								sides[1] = true;
							}
							else if (objects[j]->GetX() == objects[i]->GetX() && objects[i]->GetY() - objects[j]->GetY() == 30)
							{
								sides[2] = true;
							}
							else if (objects[i]->GetX() - objects[j]->GetX() == 30 && objects[i]->GetY() - objects[j]->GetY() == 30)
							{
								sides[3] = true;
							}
							else if (objects[i]->GetX() - objects[j]->GetX() == 30 && objects[i]->GetY() == objects[j]->GetY())
							{
								sides[4] = true;
							}
							else if (objects[i]->GetX() - objects[j]->GetX() == 30 && objects[j]->GetY() - objects[i]->GetY() == 30)
							{
								sides[5] = true;
							}
							else if (objects[j]->GetX() == objects[i]->GetX() && objects[j]->GetY() - objects[i]->GetY() == 30)
							{
								sides[6] = true;
							}
							else if (objects[j]->GetX() - objects[i]->GetX() == 30 && objects[j]->GetY() - objects[i]->GetY() == 30)
							{
								sides[7] = true;
							}
						}
					}
					for (int j = 0; j < 8; j++)
					{
						if (sides[j] == true)
						{
							fout << 1 << " ";
						}
						else
						{
							fout << 0 << " ";
						}
					}
				}
				fout << endl;
			}
			fout.close();
		}

		window->Update(0.f);

		app_window.clear(sf::Color::Black);
		app_window.draw(backgroundImage);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			sf::Sprite s;

			if (radioWall->IsActive())
				s.setTexture(*wallTexturesT[(int)wallTexture->GetValue()]);
			else if (radioItem->IsActive())
				s.setTexture(*itemTexturesT[(int)itemTexture->GetValue()]);
			else if (radioSpike->IsActive())
				s.setTexture(*spikeTexturesT[(int)spikeTexture->GetValue()]);
			else if (radioCannon->IsActive())
				s.setTexture(*cannonTexturesT[(int)cannonTexture->GetValue()]);
			else if (radioGravity->IsActive())
				s.setTexture(*gravityTexturesT[(int)gravityTexture->GetValue()]);
			else if (radioDecoration->IsActive())
				s.setTexture(*decorationTexturesT[(int)decorationTexture->GetValue()]);
			s.setPosition(sf::Vector2f(sf::Mouse::getPosition(app_window)));
			if (!radioDecoration->IsActive())
			{
				s.setScale(sf::Vector2f(2.f,2.f));
			}
			app_window.draw(s);
			 lWasPressed = true;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		{
			rWasPressed = true;
		}

		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->Draw(app_window);
		}

		
		sfgui.Display(app_window);
		app_window.display();
	}

	return EXIT_SUCCESS;
}