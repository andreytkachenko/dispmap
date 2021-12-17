use image::{buffer::PixelsMut, GrayImage, Luma, RgbImage, GenericImageView, Rgb};

fn diff(left: Rgb<u8>, right: Rgb<u8>) -> i32 {
    let r = (left[0] as i32 - right[0] as i32).abs();
    let g = (left[1] as i32 - right[1] as i32).abs();
    let b = (left[2] as i32 - right[2] as i32).abs();

    let color = (g - r).abs() + (b - g).abs();

    (r + g + b) + color * 4
}

fn match_box(left: [Rgb<u8>; 16], right: [Rgb<u8>; 16]) -> i32 {
    let mut sqr_sum = 0;

    for (l, r) in left.into_iter().zip(right.into_iter()) {
        sqr_sum += diff(l, r);
    }

    sqr_sum
}

fn px(img: &RgbImage, x: u32, y: u32) -> Rgb<u8> {
    if x >= img.width() || y >= img.height() {
        return Rgb([0,0,0]);
    }

    img.get_pixel(x, y).clone()
}

fn match_pixels(left: &RgbImage, right: &RgbImage, x: u32, y: u32, j: u32) -> i32 {
    let lx = x;
    let rx = x + j;

    match_box(
        [
            px(left, lx, y    ), px(left, lx + 1, y    ), px(left, lx + 2, y    ), px(left, lx + 3, y    ),
            px(left, lx, y + 1), px(left, lx + 1, y + 1), px(left, lx + 2, y + 1), px(left, lx + 3, y + 1),
            px(left, lx, y + 2), px(left, lx + 1, y + 2), px(left, lx + 2, y + 2), px(left, lx + 3, y + 2),
            px(left, lx, y + 3), px(left, lx + 1, y + 3), px(left, lx + 2, y + 3), px(left, lx + 3, y + 3),
        ],
        [
            px(right, rx, y    ), px(right, rx + 1, y    ), px(right, rx + 2, y    ), px(right, rx + 3, y    ),
            px(right, rx, y + 1), px(right, rx + 1, y + 1), px(right, rx + 2, y + 1), px(right, rx + 3, y + 1),
            px(right, rx, y + 2), px(right, rx + 1, y + 2), px(right, rx + 2, y + 2), px(right, rx + 3, y + 2),
            px(right, rx, y + 3), px(right, rx + 1, y + 3), px(right, rx + 2, y + 3), px(right, rx + 3, y + 3),
        ]

    )
}

fn get_pixel_color(image: &RgbImage, cursor: i32) -> f32 {
    if cursor == 0 {
        return 0.0;
    }

    (10 * image.width()) as f32 / (2.0 * 0.9 * cursor as f32)
}

fn get_pixel_hue(image: &RgbImage, x: u32, y: u32) -> i32 {
    let pixel = image.get_pixel(x, y);

    (pixel[1] as i32 - pixel[0] as i32).abs() + (pixel[2] as i32 - pixel[1] as i32).abs()
}

fn exec<'a>(res: PixelsMut<'a, Luma<u8>>, left: &RgbImage, right: &RgbImage, line: u32) {
    let mut cursor = 0i32;

    let window_size = 128u32;

    for (x, res) in res.enumerate() {
        let mut closest = -1i32;
        let mut min_error = -1i32;
        let mut matched = 0;

        let _val = get_pixel_hue(left, x as _, line);

        for i in 1..window_size {
            let _dist = (cursor - i as i32).abs();
            let tmp = match_pixels(left, right, x as _, line as _, i as _);
            let tmp_smoothed = tmp; // + (dist) * (1.0 / diff);

            if tmp_smoothed < min_error || min_error == -1 {
                min_error = tmp_smoothed;
                closest = i as i32;
                matched = 1;
            } else if tmp_smoothed == min_error
                && ((cursor - i as i32).abs() < (cursor - closest).abs())
            {
                closest = i as i32;
                matched += 1;
            }
        }

        if matched == 1 {
            cursor = closest;
        }

        *res = Luma([get_pixel_color(left, cursor) as u8]);
    }
}

pub fn compute(left: &RgbImage, right: &RgbImage) -> GrayImage {
    let mut out = GrayImage::new(left.width(), right.height());

    out.rows_mut()
        .enumerate()
        .for_each(|(y, row)| exec(row, left, right, y as _));

    out
}
