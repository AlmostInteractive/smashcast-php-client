<?php

declare(strict_types=1);

namespace SmashcastApi\Api;

use GuzzleHttp\Exception\GuzzleException;


class ChannelsApi extends AbstractApiBase
{
    /**
     * @throws GuzzleException
     */
    public function getChannel(string $channelId, string $accessToken, ?int $from = null, ?int $to = null): ?array
    {
        if (!$from)
            $from = 0;
        if (!$to)
            $to = time();

        $response = $this->apiGet("streamoverallstats/$channelId/$from/{$to}000", [], $accessToken);
        $data = json_decode($response->getBody()->getContents(), true);
        return isset($data['channel']) ? $data : null;
    }

    /**
     * @throws GuzzleException
     */
    public function getVideos(string $channelId): ?array
    {
        $response = $this->apiGet("media/video/$channelId/list");
        $data = json_decode($response->getBody()->getContents(), true);
        if (isset($data['success']) && $data['success'] === false)
            return null;

        function extractData($video) {
            return [
                'id' => $video['media_id'],
                'date' => $video['media_date_added'],
                'title' => $video['media_title'],
                'duration' => $video['duration'],
                'category' => $video['category_name'],
                'thumbnail' => $video['media_thumbnail']
            ];
        }

        return array_map('extractData', $data['videos']);
    }
}
