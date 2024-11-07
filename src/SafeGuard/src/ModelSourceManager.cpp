#include "SafeGuard/ModelSourceManager.h"
#include "Common/IFilesystem.h"

namespace SafeGuard
{


    bool ModelSourceManager::Initialize(const std::string &model_dir)
    {
        using namespace Common::IFilesystem;
        if(!IsExist(model_dir)) return false;

        if(IsDir(model_dir)) {
            auto list = ListDir(model_dir);
            for(const auto& path : list) {
                if(IsEndWith(path, ".onnx")) {
                    m_filename2path.insert({GetFilename(path), path});
                }
            }
        }else if(IsEndWith(model_dir, ".onnx")) {
            m_filename2path.insert({GetFilename(model_dir), model_dir});
        }
        return true;
    }

    std::string ModelSourceManager::GetModelPath(const std::string &model_name) const
    {
        std::string path;
        if(m_filename2path.count(model_name)) {
            path = m_filename2path.at(model_name);
        }

        return path;
    }

    std::vector<std::string> ModelSourceManager::GetAllModelNames() const
    {
        std::vector<std::string> modelNames;
        for(const auto& iter : m_filename2path) {
            modelNames.emplace_back(iter.first);
        }

        return modelNames;
    }

    
} // namespace SafeGuard

