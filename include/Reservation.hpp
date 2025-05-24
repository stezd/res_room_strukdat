#ifndef RESERVATION_HPP
#define RESERVATION_HPP

#include <string>
#include <nlohmann/json.hpp>

class Reservation {
public:
    Reservation() = default;

    Reservation(const std::string &id, const std::string &nama, const std::string &nim,
                const std::string &ruangan, const std::string &tanggal,
                const std::string &jamMulai, const std::string &jamSelesai,
                const std::string &status);

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

    static Reservation from_json(const nlohmann::json &j);

    nlohmann::json to_json() const;

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

// JSON serialization
void to_json(nlohmann::json &j, const Reservation &r);

void from_json(const nlohmann::json &j, Reservation &r);

#endif
