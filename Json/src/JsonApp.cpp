#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "cinder\Json.h"

using namespace ci;
using namespace ci::app;

class JsonApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void JsonApp::setup()
{
	//　jsonの読みこみ
	ci::JsonTree json(loadAsset("test.json"));

	//　取り出し方
	const auto& player = json["Player"];
	auto name = player["Name"].getValue<std::string>();
	auto hp = player["HP"].getValue<int>();
	auto speed = player["Speed"].getValue<float>();

	console() << name << " " << hp << " " << speed << std::endl;

	//　配列の取り出し方
	const auto& enemy_names = json["Enemy"]["array"];
	auto dragon = enemy_names[0].getValue<std::string>();
	auto array = enemy_names.getChildren();
	auto names = json["Enemy"]["Name"].getChildren();
	for(auto& enemy : array)
	{
		console() << enemy.getValue() << std::endl;
	}
	for (auto& name : names)
	{
		console() << name.getValue<std::string>() << std::endl;
	}

	//　別の書き方
	const auto& other = json["Player.Name"].getValue<std::string>();
	console() << other << std::endl;


	//　書き出し
	ci::JsonTree json_write = ci::JsonTree::makeObject("Person");
	json_write.addChild(ci::JsonTree("name", "arai"))
		.addChild(ci::JsonTree("hp", 10));

	//　第二引数にci::JsonTree::WriteOptions().createDocument()を入れないとPersonが出力されない
	json_write.write(app::getAppPath() / "write.json", ci::JsonTree::WriteOptions().createDocument());

}

void JsonApp::mouseDown( MouseEvent event )
{
}

void JsonApp::update()
{
}

void JsonApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( JsonApp, RendererGl )
