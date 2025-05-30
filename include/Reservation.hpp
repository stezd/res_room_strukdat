#pragma once

#include <string>
#include <nlohmann/json.hpp>

class Reservation {
public:
    Reservation() = default;
    
    Reservation(const std::string &id, const std::string &nama, const std::string &nim,
                const std::string &ruangan, const std::string &tanggal,
                const std::string &jamMulai, const std::string &jamSelesai,
                const std::string &status)
        : id(id), nama(nama), nim(nim), ruangan(ruangan), tanggal(tanggal),
          jamMulai(jamMulai), jamSelesai(jamSelesai), status(status) {
    }

    const std::string &getId() const { return id; }
    const std::string &getNama() const { return nama; }
    const std::string &getNim() const { return nim; }
    const std::string &getRuangan() const { return ruangan; }
    const std::string &getTanggal() const { return tanggal; }
    const std::string &getJamMulai() const { return jamMulai; }
    const std::string &getJamSelesai() const { return jamSelesai; }
    const std::string &getStatus() const { return status; }

    void setId(const std::string &value) { id = value; }
    void setNama(const std::string &value) { nama = value; }
    void setNim(const std::string &value) { nim = value; }
    void setRuangan(const std::string &value) { ruangan = value; }
    void setTanggal(const std::string &value) { tanggal = value; }
    void setJamMulai(const std::string &value) { jamMulai = value; }
    void setJamSelesai(const std::string &value) { jamSelesai = value; }
    void setStatus(const std::string &value) { status = value; }

    static Reservation from_json(const nlohmann::json &j) {
        try {
            Reservation r;
            r.setId(j.at("id").get<std::string>());
            r.setNama(j.at("nama").get<std::string>());
            r.setNim(j.at("nim").get<std::string>());
            r.setRuangan(j.at("ruangan").get<std::string>());
            r.setTanggal(j.at("tanggal").get<std::string>());
            r.setJamMulai(j.at("jamMulai").get<std::string>());
            r.setJamSelesai(j.at("jamSelesai").get<std::string>());
            r.setStatus(j.at("status").get<std::string>());
            return r;
        } catch (const nlohmann::json::exception &e) {
            throw std::runtime_error("Failed to parse JSON: " + std::string(e.what()));
        }
    }

    nlohmann::json to_json() const {
        try {
            nlohmann::json j = {
                {"id", id},
                {"nama", nama},
                {"nim", nim},
                {"ruangan", ruangan},
                {"tanggal", tanggal},
                {"jamMulai", jamMulai},
                {"jamSelesai", jamSelesai},
                {"status", status}
            };
            return j;
        } catch (const nlohmann::json::exception &e) {
            throw std::runtime_error("Failed to create JSON: " + std::string(e.what()));
        }
    }

private:
    std::string id;
    std::string nama;
    std::string nim;
    std::string ruangan;
    std::string tanggal;
    std::string jamMulai;
    std::string jamSelesai;
    std::string status;
};

inline void to_json(nlohmann::json &j, const Reservation &r) {
    j = r.to_json();
}

inline void from_json(const nlohmann::json &j, Reservation &r) {
    r = Reservation::from_json(j);
}