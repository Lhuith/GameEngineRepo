#ifndef DEBUG_PROFILER_H
#define DEBUG_PROFILER_H
#include <Misc\TypeDefs.h>

using ee::uint;
namespace Profiling
{
	class __declspec(dllexport) Profiler
	{
	public:
		static const uint MAX_FRAME_SAMPLES = 1000;
		static Profiler& getInstance();
	private:
		Profiler() {}
		Profiler(const Profiler&);
		Profiler& operator=(const Profiler&);
		static Profiler theInstance;
#if PROFILING_ON
		const char* fileName;
		bool status;
		static const uint MAX_PROFILE_CATAGORIES = 20;
		uint frameIndex;
		uint categoryIndex;
		uint numUsedCategories;
		struct ProfileCategory
		{
			const char* name;
			float samples[MAX_FRAME_SAMPLES];
		} categories[MAX_PROFILE_CATAGORIES];
		void writeData() const;
		void writeFrame(uint frameNumber) const;
		char getDelimiter(uint index) const;
		bool currentFrameComplete() const;
		bool wrapped() const;
		void checkforDuplicateCategory(const char* category);
#endif
	public:
#if PROFILING_ON
		void initalize(const char* fileName);
		void shutdown();
		void newFrame();
		void addEntry(const char* category, float time);
		void checkStatus(bool* status) const;
#else
		void initalize(const char* fileName) {}
		void shutdown() {}
		void newFrame() {}
		void addEntry(const char* category, float time) {}
		void checkStatus(bool* status) const {}
#endif
	};

#define profiler Profiling::Profiler::getInstance()
}
#endif