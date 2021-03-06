#include "uwp.hpp"
#include <winrt/Windows.Storage.h>

concurrency::task<const winrt::Windows::ApplicationModel::StartupTask *> UWP::GetApplicationStartupTask()
{
	return concurrency::create_task([]() -> const winrt::Windows::ApplicationModel::StartupTask *
	{
		static const auto task = winrt::Windows::ApplicationModel::StartupTask::GetForCurrentPackageAsync().get().GetAt(0);
		return &task;
	});
}

winrt::hstring UWP::GetApplicationFolderPath(const FolderType &type)
{
	static const auto application_data = winrt::Windows::Storage::ApplicationData::Current();

	switch (type)
	{
	case FolderType::Temporary:
		return application_data.TemporaryFolder().Path();

	case FolderType::Roaming:
		return application_data.RoamingFolder().Path();

	// Apparently we can cast any integer to an enum class, so yeah...
	default:
		throw std::invalid_argument("type was not one of the known values");
	}
}