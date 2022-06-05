import Hermod;

#include <memory>

int main(int argc, char* argv[])
{
	std::shared_ptr<Hermod::ConsoleSink> consoleSink = std::make_shared<Hermod::ConsoleSink>();

	Hermod::Logger logger({ consoleSink });
	logger.SetLevel(Hermod::ELevel::Trace);
	logger.Log<Hermod::ELevel::Trace>("Trace");
	logger.Log<Hermod::ELevel::Error>("Error");
	logger.Log<Hermod::ELevel::Error>("Error");
	logger.Log<Hermod::ELevel::Error>("Error");

	return 0;
}