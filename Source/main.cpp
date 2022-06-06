import Hermod;

#include <memory>

int main(int argc, char* argv[])
{
	std::shared_ptr<Hermod::ConsoleSink> consoleSink = std::make_shared<Hermod::ConsoleSink>();
	std::shared_ptr<Hermod::FileSink> fileSink = std::make_shared<Hermod::FileSink>("myfolder/log.txt");

	Hermod::Logger logger({ consoleSink, fileSink });
	logger.SetLevel(Hermod::ELevel::Trace);
	logger.Log<Hermod::ELevel::Trace>("Trace");
	logger.Log<Hermod::ELevel::Error>("Error");
	logger.Log<Hermod::ELevel::Error>("Error");
	logger.Log<Hermod::ELevel::Error>("Error");

	return 0;
}