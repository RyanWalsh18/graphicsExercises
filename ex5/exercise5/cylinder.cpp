#include "cylinder.hpp"
#include "../vmlib/mat33.hpp"

SimpleMeshData make_cylinder(bool aCapped, std::size_t aSubdivs, Vec3f aColor, Mat44f aPreTransform)
{
	// TODO: implement me
	std::vector<Vec3f> pos;
	std::vector<Vec3f> normals;

	float prevY = std::cos(0.f);
	float prevZ = std::sin(0.f);

	for (std::size_t i = 0; i < aSubdivs; ++i)
	{
		float const angle = (i + 1) / float(aSubdivs) * 2.f * 3.1415926f;
		float y = std::cos(angle);
		float z = std::sin(angle);

		// two triangles (3*2 positions) create one segment of the cylinder's shell

		if (aCapped)
		{
			// cap
			pos.emplace_back(Vec3f{0.f, prevY, prevZ});
			pos.emplace_back(Vec3f{0.f, 0.f, 0.f}); // middle left
			pos.emplace_back(Vec3f{0.f, y, z});

			normals.emplace_back(Vec3f{-1.f, 0.f, 0.f});
			normals.emplace_back(Vec3f{-1.f, 0.f, 0.f});
			normals.emplace_back(Vec3f{-1.f, 0.f, 0.f});

			// link
			pos.emplace_back(Vec3f{0.f, prevY, prevZ});
			normals.emplace_back(Vec3f{0.f, prevY, prevZ});

			pos.emplace_back(Vec3f{0.f, y, z});
			normals.emplace_back(Vec3f{0.f, y, z});

			pos.emplace_back(Vec3f{1.f, prevY, prevZ});
			normals.emplace_back(Vec3f{0.f, prevY, prevZ});

			pos.emplace_back(Vec3f{0.f, y, z});
			normals.emplace_back(Vec3f{0.f, y, z});

			pos.emplace_back(Vec3f{1.f, y, z});
			normals.emplace_back(Vec3f{0.f, y, z});

			pos.emplace_back(Vec3f{1.f, prevY, prevZ});
			normals.emplace_back(Vec3f{0.f, prevY, prevZ});

			// cap
			pos.emplace_back(Vec3f{1.f, y, z});
			pos.emplace_back(Vec3f{1.f, 0.f, 0.f}); // middle right
			pos.emplace_back(Vec3f{1.f, prevY, prevZ});

			normals.emplace_back(Vec3f{1.f, 0.f, 0.f});
			normals.emplace_back(Vec3f{1.f, 0.f, 0.f});
			normals.emplace_back(Vec3f{1.f, 0.f, 0.f});
		}
		else
		{
			pos.emplace_back(Vec3f{0.f, prevY, prevZ});
			normals.emplace_back(Vec3f{0.f, prevY, prevZ});

			pos.emplace_back(Vec3f{0.f, y, z});
			normals.emplace_back(Vec3f{0.f, y, z});

			pos.emplace_back(Vec3f{1.f, prevY, prevZ});
			normals.emplace_back(Vec3f{0.f, prevY, prevZ});

			pos.emplace_back(Vec3f{0.f, y, z});
			normals.emplace_back(Vec3f{0.f, y, z});

			pos.emplace_back(Vec3f{1.f, y, z});
			normals.emplace_back(Vec3f{0.f, y, z});

			pos.emplace_back(Vec3f{1.f, prevY, prevZ});
			normals.emplace_back(Vec3f{0.f, prevY, prevZ});
		}

		prevY = y;
		prevZ = z;
	}

	for (auto &p : pos)
	{
		Vec4f p4{p.x, p.y, p.z, 1.f};
		Vec4f t = aPreTransform * p4;
		t /= t.w;

		p = Vec3f{t.x, t.y, t.z};
	}

	Mat33f const N = mat44_to_mat33(transpose(invert(aPreTransform)));
	for (auto &p : normals)
	{
		Vec3f p4{p.x, p.y, p.z};
		Vec3f t = N * p4;

		p = Vec3f{t.x, t.y, t.z};
	}

	std::vector col(pos.size(), aColor);

	return SimpleMeshData{std::move(pos), std::move(col), std::move(normals)};
}
